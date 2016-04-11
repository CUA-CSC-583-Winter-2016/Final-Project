#ifndef HEAD_TRACKER_H
#define HEAD_TRACKER_H

#include <stdint.h>

/**
  Will locate the x and y coordinates of the head the head using background and current depth data from the kinect.
  Pointers `background` and `current` point to arrays in column major format. current[y][x] == current [y*width+x].
  @param background A pointer to a snapshot of the depth of the background.
  @param current A pointer to current depth array,
  @param width Width of background and current.
  @param height Height background and current.
  @param x A pointer for the resulting x coordinate
  @param y A pointer for the resulting y coordinate
  @param z A pointer for the resulting z coordinate
*/
void locate_head(const uint16_t *background, const uint16_t *current, int width, int height, int *x, int *y, uint16_t *z);

#endif
