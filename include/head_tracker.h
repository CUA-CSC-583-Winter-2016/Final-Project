#ifndef HEAD_TRACKER_H
#define HEAD_TRACKER_H

#include <stdint.h>

/*
  Will locate the x and y coordinates of the head the head using background and current depth data from the kinect.
  Pointers `background` and `current` point to arrays in column major format. current[y][x] == current [y*width+x].
*/
void locate_head(const uint16_t *background, const uint16_t *current, int width, int height, int *x, int *y);

#endif
