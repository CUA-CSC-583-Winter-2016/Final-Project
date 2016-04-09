#include "head_tracker.h"

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
void locate_head(const uint16_t *background, const uint16_t *current, int width, int height, int *x, int *y, uint16_t *z){
  *x=width/2;
  *y=width/2;
  *z=100;
}
