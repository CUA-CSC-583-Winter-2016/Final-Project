#include "head_tracker.h"
#include <math.h>
#define M_PI 3.14159265358979323846

/*
  Just a note,
  Certain numbers represent errors where the depth can't be determined.
  These numbers will almost certainly exist in both the `background` and `current` arrays.
  too near	0x0000
  too far	0x0FFF
  unknown	0x1FFF
*/
// Error numbers for convienience ;)
#define TOO_NEAR 0x0000
#define TOO_FAR 0x0FFF
#define UNKNOWN 0x1FFF
float rotation = 0;
void locate_head(const uint16_t *background, const uint16_t *current, int width, int height, int *headx, int *heady, uint16_t *headz){

  int x = 0;
  int y = 0;
  int found = 0;
  for (y = 0; y < width && !found; y++) {
    for (x = 0; x < height && !found; x++) {
      uint16_t difference = current[x + y*width] - background[x + y*width];
      if (abs(difference)) {
        *headx = x;
        *heady = y;
        *headz = current[*headx + *heady*width];
        return;
      }
    }
  }
}
