#include "kinect_interface.h"
#include <libfreenect/libfreenect.h>

int init_kinect() {
  return 0;
}

void get_depth(uint16_t *buffer) {
  for (int i = 0; i < 640*480; i++) {
    buffer[i] = 10;
  }
}
