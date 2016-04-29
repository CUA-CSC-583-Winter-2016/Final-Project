#include "head_tracker.h"
#include "stdlib.h"
#define M_PI 3.14159265358979323846

/*
  Just a note,
  Certain numbers represent errors where the depth can't be determined.
  These numbers will almost certainly exist in both the `background` and `current` arrays.

  Error numbers for convienience ;)

*/

  //Maximum value that a uint16_t pixel will take on in the buffer of any of the FREENECT_DEPTH_11BIT, FREENECT_DEPTH_10BIT, FREENECT_DEPTH_11BIT_PACKED, or FREENECT_DEPTH_10BIT_PACKED frame callbacks
  #define FREENECT_DEPTH_RAW_MAX_VALUE 2048

  //Value indicating that this pixel has no data, when using FREENECT_DEPTH_11BIT, FREENECT_DEPTH_10BIT, FREENECT_DEPTH_11BIT_PACKED, or FREENECT_DEPTH_10BIT_PACKED
  #define FREENECT_DEPTH_RAW_NO_VALUE 2047

void locate_head(const uint16_t *background, const uint16_t current[], int width, int height, int *headx, int *heady, uint16_t *headz){

  int x;
  int y;
  uint16_t f = FREENECT_DEPTH_RAW_MAX_VALUE;
  // The +- 1 offset buisness in the for loops makes sure we can always see the crosshairs.
  for (y = 100; y < height-100; y++) {
    for (x = 100; x < width-100; x++) {
      uint16_t difference = current[x + y*width] - background[x + y*width];
      //if (abs(difference) < 10) {
      // For debuging purposes and just for fun, I've modified this code to locate the closest point to the kinect.
      if (current[x + y*width] < f) {
        f = current[x + y*width];
        *headx = x;
        *heady = y;
        //return;
      }
    }
  }
  *headz = current[*headx + *heady*width];
}
