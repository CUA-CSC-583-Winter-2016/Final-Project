#include <GL/glew.h>
#include "shaders.h"
#include <stdio.h>
// #define DEBUG

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
GLuint boxMatrixLocation;
// I know they're global variables, I'll put these in a struct in the future so that multiple cubes can be defined.

void load_shader() {
  // vertex shader
  GLuint boxVertShader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar *vertexShader = _binary_source_vertex_glsl_start;
  const GLint vertexShaderSize = (int)(long)&_binary_source_vertex_glsl_size;
  glShaderSource(boxVertShader, 1, &vertexShader, &vertexShaderSize);
  glCompileShader(boxVertShader);
  #ifdef DEBUG
    printf("vertex shader %i characters\n",vertexShaderSize);
    printf("%.*s",vertexShaderSize,vertexShader);
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
  glShaderSource(boxFragShader, 1, &fragmentShader, &fragmentShaderSize);
  glCompileShader(boxFragShader);
  #ifdef DEBUG
    printf("fragment shader %i characters\n",fragmentShaderSize);
    printf("%.*s\n",fragmentShaderSize,fragmentShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      printf("%s\n",infoLog);
    } else {
      printf("success\n");
    }
  #endif

  // program
  boxShaderProgram = glCreateProgram();
  glAttachShader(boxShaderProgram, boxVertShader);
  glAttachShader(boxShaderProgram, boxFragShader);
  glLinkProgram(boxShaderProgram);
  glDeleteShader(boxVertShader);
  glDeleteShader(boxFragShader);
  #ifdef DEBUG
    glGetProgramiv(boxShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(boxShaderProgram, 512, NULL, infoLog);
      printf("Failure\n%s\n",infoLog);
    } else {
     printf("success\n");
    }
  #endif

  boxMatrixLocation = glGetUniformLocation(boxShaderProgram, "matrix");
}

void load_cube() {
  load_shader();

  glGenVertexArrays(1, &boxVAO);
  glBindVertexArray(boxVAO);

  glGenBuffers(1,&boxVBO);
  glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(boxVerticies), boxVerticies, GL_STATIC_DRAW);

  glGenBuffers(1,&boxEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,boxEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxElements), boxElements, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  glBindVertexArray(0);
}

void set_cube_matrix(GLfloat *matrix) {
  glUseProgram(boxShaderProgram);
  glUniformMatrix4fv(boxMatrixLocation, 1, GL_TRUE, matrix);
}

void draw_cube(){
  glUseProgram(boxShaderProgram);
  glBindVertexArray(boxVAO);
  glLineWidth(4);
  glDrawElements(GL_LINES,24,GL_UNSIGNED_INT,0);
  glBindVertexArray(0);
}

void destroy_cube(){
  // Ehh, I really don't want to destroy my beautiful cube.
  glDeleteVertexArrays(1, &boxVAO);
  glDeleteBuffers(1, &boxVBO);
  glDeleteBuffers(1, &boxEBO);
  glDeleteProgram(boxShaderProgram);
}

void set_clear_color(GLfloat r, GLfloat g, GLfloat b) {
  glClearColor(r,g,b,1.0);
}

void clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}
