/**
  @author Michael Monaghan
*/

#include <stdio.h>
#include <stdint.h>
#include "opengl_window.h"
#include "opengl_rendering.h"
#include "kinect_interface.h"
#include "head_tracker.h"
#include "matrix_math.h"
#define DEBUG

// RUN TIME CONSTANTS
// #############################################################################
// Kinect position. Origin is center of screen.
float KX = 0; // X in cm relative to screen. Positive is right when looking at screen.
float KY = 0; // Y in cm relative to screen. Positive is up.
float KZ = 0; // Z in cm relative to screen. Positive is the direction the screen is facing.
float KA = 0; // Angle in radians from the normal of the screen to the direction of the Kinect.
// #############################################################################

void printmat(GLfloat *m) {
  printf("%.2f\t%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\t%.2f\n",
      m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
}

int main (int argc, const char *argv[]) {
  printf("Good news everyone, it's compiling!\n"); //TODO remove futurama reference and actually glue all the code together.

  // Setup Window, OpenGL, and Kinect.
  create_window();
  init_kinect();
  set_clear_color(0.0,0.0,0.0);
  load_cube();

  // Here's some arrays for the depth from the kinect.
  uint16_t c[640*480]; // Current depth
  uint16_t b[640*480]; // Background depth

  // Wait a bit for the kinect to initialize and get the background depth. 300 gets seems to work.
  for (int i = 0; i < 300; i++)
    get_depth(b);

  // Fill the holes in the background.
  fill_depth(b);

  #ifdef DEBUG
    unsigned char count;
  #endif

  // Setup those variables to remain thoughtout loop.
  int cx = 0, cy = 0; // Kinect camera x y
  uint16_t cz = 0; // Kinect camera z
  while(!should_close_window()) {
    // locate head
    get_depth(c);
    locate_head(b, c, 640,480, &cx, &cy, &cz);

    // unproject kinect camera coord.
    GLfloat k_eye[4]; k_eye[3] = 1;
    unproject_kinect_coords(cx,cy,cz,&k_eye[0],&k_eye[1],&k_eye[2]);

    // TODO rotate and translate kinect camera coord to global space.
    /*
    GLfloat tm[4*4] = {
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1}; // transform matrix;
    */
    /*
    GLfloat theta = 0;
    GLfloat phi = 0;
    GLfloat psi = 0;
    GLfloat x_scale = 1;
    GLfloat y_scale = 1;
    GLfloat z_scale = 1;
    GLfloat x_trans = 0;
    GLfloat y_trans = 0;
    GLfloat z_trans = 0;
    scale_rot_trans(tm, theta, phi, psi, x_scale, y_scale, z_scale, x_trans, y_trans, z_trans);
    */
    //mat_mult(tm,k_eye,g_eye,4,4,1);

    GLfloat k_offset[3] = {KX,KY,KZ};
    GLfloat g_eye[4]; g_eye[3] = 1;
    kinect_rot_trans_thingy(k_offset,  KA, k_eye, g_eye);



    // Calculate and set perspective transform
    GLfloat m[4*4]; // Transform matrix.
    eye_proj_mat(-8.0,8.0,6.0,-6.0,10.0,g_eye, m);
    set_cube_matrix(m);

    // Output debug info
    #ifdef DEBUG
      if (count < 10) {
        count++;
      } else {
        count = 0;
        printf("\033[2Jkinect local camera coord:\n(%i,%i,%i)\n",cx,cy,cz);
        printf("kinect local unprojected coord:\n(%f,%f,%f,%f)\n",k_eye[0],k_eye[1],k_eye[2],k_eye[3]);
        printf("global eye coord:\n(%f,%f,%f,%f)\n",g_eye[0],g_eye[1],g_eye[2],g_eye[3]);
        printmat(m);
      }
    #endif

    // render
    clear();
    draw_cube();
    swap_buffers();
  }
  destroy_cube();
  close_window();
  shutdown_kinect();
  return 0;
}
