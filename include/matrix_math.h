#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
#include <stdint.h>
#include <GL/glew.h>

//This is a useful comment

/**
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
void eye_proj_mat(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat far, const GLfloat *eye, GLfloat *mat);

/**
  Unproject x, y, and depth to rectangular coordinates.
  See graphics/kinect_coords_to_real_space.png
  @param xin x coordinate for pixel.
  @param yin y coordinate for pixel.
  @param zin depth value at pixel (x,y).
  @param outx resulting x in rectangular coordinates
  @param outy resulting y in rectangular coordinates
  @param outz resulting z in rectangular coordinates
*/
void unproject_kinect_coords(int xin, int yin, uint16_t zin, GLfloat *outx, GLfloat *outy, GLfloat *outz);

/**
  Performs matrix multiplication m1 * m2 = m3.
  @param m1 first matrix.
  @param m2 second matrix.
  @param m3 result matrix.
  @param c1 columns of first matrix.
  @param r1 rows of first matrix.
  @param c2 columns of second matrix.
*/
void mat_mult(const GLfloat *m1, const GLfloat *m2, GLfloat *m3, int r1, int c1, int c2);

#endif
