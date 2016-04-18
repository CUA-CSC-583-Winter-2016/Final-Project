#include "kinect_interface.h"
#include <libfreenect.h>
#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846

int init_kinect() {
  return 0;
}
float depth_rotation = 0;
void get_depth(uint16_t *buffer) {
  for (int i = 0; i < 640*480; i++) {
    buffer[i] = 2000+1000*sin(depth_rotation);
  }
  depth_rotation += .05;
  if(depth_rotation > 2 * M_PI)
    depth_rotation -= 2 * M_PI;
}
