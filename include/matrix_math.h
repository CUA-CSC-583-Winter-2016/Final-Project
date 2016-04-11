#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
#include <stdint.h>
#include <GL/glew.h>

/*
  Calculates the projection matrix assuming that the screen lays on the xy plane. everything behind it in -z will be in view.
  See graphics/proj_matrix.png
  @param left x value for left side of screen relative to origin.
  @param right x value for right side of screen.
  @param top y value for top of screen.
  @param bottom y value for bottom of screen.
  @param far far clipping plane (positive value). The near clipping plane will be the screen.
  @param eye pointer to eye vector.
  @param mat matrix output, row major.
*/
void eye_proj_mat(float left, float right, float top, float bottom, float far, const float *eye, float *mat);

/*
  Unproject x, y, and depth to rectangular coordinates.
  See graphics/kinect_coords_to_real_space.png
  @param xin x coordinate for pixel.
  @param yin y coordinate for pixel.
  @param zin depth value at pixel (x,y).
  @param outx output
*/
void unproject_kinect_depth(int xin, int yin, uint16_t zin, float *outx, float *outy, float *outz);

void mat_mult(GLfloat *m1, GLfloat *m2, GLfloat *m3, int r1, int c1, int c2);

#endif
