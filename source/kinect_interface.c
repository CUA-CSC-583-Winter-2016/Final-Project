#include "kinect_interface.h"
#include <libfreenect.h>
#include <math.h>
#include <stdio.h>


freenect_context *f_ctx;
freenect_device *f_dev;

void depth_callback(freenect_device *dev, void *v_depth, uint32_t timestamp) {
  // Just an empty callback
}

int init_kinect() {
  //init kinect
  freenect_init(&f_ctx,NULL);
  freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_CAMERA));
  if (!freenect_num_devices(f_ctx)) {
    printf("No devices found\n");
    freenect_shutdown(f_ctx);
    return 1;
  }
  freenect_open_device(f_ctx,&f_dev,0);
  freenect_frame_mode fm = freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM,FREENECT_DEPTH_11BIT);
  printf("width:\t%i\nheight:%i\nbytes:%i\n",fm.width,fm.height,fm.bytes);
  freenect_set_depth_mode(f_dev,fm);
  freenect_set_depth_callback(f_dev, depth_callback);
  freenect_start_depth(f_dev);
  return 0;
}

void get_depth(uint16_t *buffer) {
  freenect_set_depth_buffer(f_dev,buffer);
  if(freenect_process_events(f_ctx) < 0) {
    return;
  }
}

void fill_depth(uint16_t *buffer) {
  uint16_t last_good_pixel = FREENECT_DEPTH_RAW_MAX_VALUE;
  for (int i = 0; i < 640*480; i++) {
    if(buffer[i] == FREENECT_DEPTH_RAW_NO_VALUE) {
      buffer[i] = last_good_pixel;
    } else {
      last_good_pixel = buffer[i];
    }
  }
}
