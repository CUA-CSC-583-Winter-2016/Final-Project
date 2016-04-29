#include "kinect_interface.h"
#include <libfreenect.h>
#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846


freenect_context *f_ctx;
freenect_device *f_dev;

void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp) {
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
  freenect_set_depth_callback(f_dev, depth_cb);
  freenect_start_depth(f_dev);

}

void get_depth(uint16_t *buffer) {
  freenect_set_depth_buffer(f_dev,buffer);
  if(freenect_process_events(f_ctx) < 0) {
    return;
  }
}
