#include <GL/glew.h>
#include "shaders.h"
#include <stdio.h>

/**
  @author Michael Monaghan
*/

/*
    3-------7   Unit Box
    |\      |\
    | 2-------6    y
    0-|-----4 | -z |
     \|      \|   \|
      1-------5    '-----x
*/
GLfloat boxVerticies[8][3] =
{
  {-1,-1,-1},{-1,-1,1},
  {-1,1,1},{-1,1,-1},

  {1,-1,-1},{1,-1,1},
  {1,1,1},{1,1,-1},
};
GLuint boxElements[12][2]={{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};

// Unique to a specific box.
GLuint boxVBO;
GLuint boxEBO;
GLuint boxVAO;
GLuint boxShaderProgram;
// I know they're global variables, I'll put these in a struct in the future so that multiple cubes can be defined.

void load_cube() {
  // vertex shader
  GLuint boxVertShader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar *vertexShader = _binary_source_vertex_glsl_start;
  const GLint vertexShaderSize = (int)(long)&_binary_source_vertex_glsl_size;
  printf("vertex shader %i characters\n",vertexShaderSize);
  printf("%.*s",vertexShaderSize,vertexShader);
  glShaderSource(boxVertShader, 1, &vertexShader, &vertexShaderSize);
  glCompileShader(boxVertShader);
  #ifdef DEBUG
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("%s\n",infoLog);
  } else {
    printf("success\n");
  }
  #endif

  // fragment shader
  GLuint boxFragShader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar *fragmentShader = _binary_source_fragment_glsl_start;
  const GLint fragmentShaderSize = (int)(long)&_binary_source_fragment_glsl_size;
  printf("fragment shader %i characters\n",fragmentShaderSize);
  printf("%.*s\n",fragmentShaderSize,fragmentShader);
  glShaderSource(boxFragShader, 1, &fragmentShader, &fragmentShaderSize);
  glCompileShader(boxFragShader);
  #ifdef DEBUG
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("%s\n",infoLog);
  } else {
    printf("success\n");
  }
  #endif
}

void draw_cube(){
  glUseProgram(boxShaderProgram);
  glBindVertexArray(boxVAO);
  glLineWidth(4);
  glDrawElements(GL_LINES,24,GL_UNSIGNED_INT,0);
}

void destroy_cube(){
  // Ehh, I really don't want to destroy my beautiful cube.
}
