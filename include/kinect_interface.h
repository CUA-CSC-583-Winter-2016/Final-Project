#ifndef KINECT_INTERFACE_H
#define KINECT_INTERFACE_H

#include <stdint.h>
/*
  Initializes and chooses a kinect.
  @return false if initialization fails.
*/
bool init_kinect();

/*
  Get depth buffer.
  @param buffer A pointer to an array for depth data. Must be at least 640 * 480 * 2 bytes in size.
*/
void get_depth(uint16_t *buffer);

#endif
