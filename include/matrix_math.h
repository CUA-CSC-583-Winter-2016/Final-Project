#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

/*
  Calculates the projection matrix assuming that the screen lays on the xy plane. everything behind it in -z will be in view.
  @param left x value for left side of screen relative to origin.
  @param right x value for right side of screen.
  @param top y value for top of screen.
  @param bottom y value for bottom of screen.
  @param far far clipping plane (positive value). The near clipping plane will be the screen.
  @param eye pointer to eye vector.
  @param mat matrix output, row major.
*/
void screen_proj_mat(float left, float right, float top, float bottom, float far, const float *eye, float *mat);

#endif
