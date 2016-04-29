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

void printmat(GLfloat *m) {
  printf("%.2f\t%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\t%.2f\n%.2f\t%.2f\t%.2f\t%.2f\n",
      m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
}

int main (int argc, const char *argv[]) {
  printf("Good news everyone, it's compiling!\n"); //TODO remove futurama reference and actually glue all the code together.
  create_window();
  init_kinect();
  set_clear_color(0.0,0.0,0.0);
  load_cube();

  GLfloat m[4*4];
  uint16_t c[640*480]; // Current depth
  uint16_t b[640*480]; // Background depth
  for (int i = 0; i < 300; i++)
    get_depth(b);
  int x=0,y=0;
  int cx = 0, cy = 0; // Kinect camera x y z
  uint16_t cz = 0;
  while(!should_close_window()) {
    // locate head
    get_depth(c);
    locate_head(b, c, 640,480, &cx, &cy, &cz);
    GLfloat kx, ky, kz; // Kinect local x y z
    unproject_kinect_coords(cx,cy,cz,&kx,&ky,&kz);
    GLfloat eye[3];
    // TODO rotate and translate kinect local coord to global space.
    eye[0] = kx; eye[1] = ky; eye[2] = kz;
    eye_proj_mat(-320.0,320.0,240.0,-240.0,200.0, eye, m); // Not working yet.
    set_cube_matrix(m);
    #ifdef DEBUG
      printf("\nhead coord:\n(%i,%i,%i)\n",cx,cy,cz);
      printf("kinect local coord:\n(%f,%f,%f)\n",kx,ky,kz);
      printf("eye coord:\n(%f,%f,%f)\n",eye[0],eye[1],eye[2]);
      printmat(m);
    #endif

    // render
    clear();
    draw_cube();
    swap_buffers();
  }
  destroy_cube();
  close_window();
  return 0;
}
