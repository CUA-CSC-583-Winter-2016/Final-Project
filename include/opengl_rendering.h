#ifndef OPENGL_OBJECTS_H
#define OPENGL_OBJECTS_H
#include <GL/glew.h>

/**
  Loads a unit cube of size 1.
*/
void load_cube();

/**
  Sets the transformation matrix for the cube. Requires cube to be loaded first.
*/
void set_cube_matrix(GLfloat *matrix);

/**
  Draws the cube that was loaded.
*/
void draw_cube();

/**
  Unloads the cube.
*/
void destroy_cube();

/**
  Sets the clearing color.
*/
void set_clear_color(float r, float g, float b);

/**
  Clears the screen with the color set by set_clear_color();
*/
void clear();

#endif
