#include <stdio.h>
#include "opengl_window.h"
#include "opengl_rendering.h"
#include "kinect_interface.h"
#include "head_tracker.h"
#include "matrix_math.h"

int main (int argc, const char *argv[]) {
  printf("Good news everyone, it's compiling!\n"); //TODO remove futurama reference and actually glew all the code together.
  create_window();
  set_clear_color(0.5,0.5,0.5);
  load_cube();
  GLfloat m[] = {
    0.5,0.0,0.0,0.0,
    0.0,0.5,0.0,0.0,
    0.0,0.0,0.5,0.2,
    0.0,0.0,0.0,1.0
  };
  set_cube_matrix(m);
  while(!should_close_window()) {
    clear();
    draw_cube();
    swap_buffers();
  }
  destroy_cube();
  close_window();
  return 0;
}
