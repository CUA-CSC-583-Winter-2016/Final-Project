#include "head_tracker.h"
#include "stdlib.h"
#define M_PI 3.14159265358979323846

// Tweakables
float A = 40000;
int BG_THRESHOLD = 70;


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
  // this loop finds the foreground.
  for(y = 1; y < height-1; y+=1) {
    for(x = 1; x < width-1; x+=1) {
      // For a pixel to be foreground, the current frame must not be unknown, and the
      if(current[x + y*width] != FREENECT_DEPTH_RAW_NO_VALUE && background[x + y*width] != FREENECT_DEPTH_RAW_NO_VALUE && (background[x + y*width]-current[x + y*width]) > BG_THRESHOLD) {
        // Find the center of the head
        int yc = y + (int) (A / current[x+y*width]);
        if (yc < 0) {
          yc = 0;
        } else if (yc > 479) {
          yc = 479;
        }
        int xl,xr;
        for(xl = x; xl >= 1 ; xl-=1) {
          if(current[xl+ yc*width] == FREENECT_DEPTH_RAW_NO_VALUE || (background[xl + yc*width]-current[xl + yc*width]) <= BG_THRESHOLD) {
            break;
          }
        }
        for(xr = x; xr < width; xr+=1) {
          if(current[xr + yc*width] == FREENECT_DEPTH_RAW_NO_VALUE || (background[xr + yc*width]-current[xr + yc*width]) <= BG_THRESHOLD) {
            break;
          }
        }
        int xc = (xl+xr)/2;
        *headx = xc;
        *heady = yc;
        *headz = current[x + yc*width];
        return;
      }

    }
  }
}
