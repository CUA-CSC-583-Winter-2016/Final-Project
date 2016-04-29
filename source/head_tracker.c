#include "head_tracker.h"
#include "stdlib.h"
#define M_PI 3.14159265358979323846

// Tweakables
float A;

/*
  Just a note,
  Certain numbers represent errors where the depth can't be determined.
  These numbers will almost certainly exist in both the `background` and `current` arrays.
*/

  //Error numbers for convienience ;)
  //Maximum value that a uint16_t pixel will take on in the buffer of any of the FREENECT_DEPTH_11BIT, FREENECT_DEPTH_10BIT, FREENECT_DEPTH_11BIT_PACKED, or FREENECT_DEPTH_10BIT_PACKED frame callbacks
  #define FREENECT_DEPTH_RAW_MAX_VALUE 2048

  //Value indicating that this pixel has no data, when using FREENECT_DEPTH_11BIT, FREENECT_DEPTH_10BIT, FREENECT_DEPTH_11BIT_PACKED, or FREENECT_DEPTH_10BIT_PACKED
  #define FREENECT_DEPTH_RAW_NO_VALUE 2047

void locate_head(const uint16_t *background, const uint16_t current[], int width, int height, int *headx, int *heady, uint16_t *headz){

  int x;
  int y;
  // The offset in the for loops makes sure we can always see the crosshairs.
  for(y = 100; y < height-100; y++) {
    for(x = 100; x < width-100; x++) {
      if(current[x + y*width] != FREENECT_DEPTH_RAW_NO_VALUE && (current[x + y*width] - background[x + y*width]) > 100) {
        int yc = y - (int)(A * current[x+y*width]);
        int xl=x,xr=x;
        for(int xltest = x; x > yc*width; x--) {
          if(current[xltest + yc*width] == FREENECT_DEPTH_RAW_NO_VALUE || (current[xltest + yc*width] - background[xltest + yc*width]) > 100) {
            xl = xltest;
            break;
          }
        }
        for(int xrtest = x; x > yc*width; x--) {
          if(current[xrtest + yc*width] == FREENECT_DEPTH_RAW_NO_VALUE || (current[xrtest + yc*width] - background[xrtest + yc*width]) > 100) {
            xr = xrtest;
            break;
          }
        }
        int xc = xl+xr/2;
        *headx = xc;
        *heady = yc;
        *headz = current[*headx + *heady*width];
        return;
      }
    }
  }
}
