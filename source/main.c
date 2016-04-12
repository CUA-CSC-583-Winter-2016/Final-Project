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

int main (int argc, const char *argv[]) {
  printf("Good news everyone, it's compiling!\n"); //TODO remove futurama reference and actually glew all the code together.
  create_window();
  init_kinect();
  set_clear_color(0.5,0.5,0.5);
  load_cube();

  GLfloat m[4*4] = { // This matrix at least works.
    0.5,0.0,0.0,0.0,
    0.0,0.5,0.0,0.0,
    0.0,0.0,0.5,0.0,
    0.0,0.0,0.25,1.0,
  };
  uint16_t c[640*480];
  uint16_t b[640*480];
  get_depth(b);
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
    //eye_proj_mat (10.0,10.0,10.0,10.0,10.0, eye, m); // Not working yet.
    set_cube_matrix(m);

    // render
    clear();
    draw_cube();
    swap_buffers();
  }
  destroy_cube();
  close_window();
  return 0;
}
