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
  Matrices must be distinct (in memory).
  @param m1 first matrix.
  @param m2 second matrix.
  @param m3 result matrix.
  @param c1 columns of first matrix.
  @param r1 rows of first matrix.
  @param c2 columns of second matrix.
*/
void mat_mult(const GLfloat *m1, const GLfloat *m2, GLfloat *m3, int r1, int c1, int c2);

void kinect_rot_trans_thingy(const GLfloat *kinectOffset, const GLfloat kinectAngle, const GLfloat *pointOffset, GLfloat *returnPoint);


/**
  Scales, rotates, and translates.
  @param m resulting transformation matrix.
  @param theta rotation about x-axis
  @param phi rotation about y-axis
  @param psi rotation about z-axis
  @param x_scale scaling on x-axis
  @param y_scale scaling on y-axis
  @param z_scale scaling on z-axis
  @param x_trans translation on x-axis
  @param y_trans translation on y-axis
  @param z_trans translation on z-axis
 */
void scale_rot_trans(GLfloat *m, GLfloat theta, GLfloat phi, GLfloat psi, GLfloat x_scale, GLfloat y_scale, GLfloat z_scale, GLfloat x_trans, GLfloat y_trans, GLfloat z_trans);

#endif
