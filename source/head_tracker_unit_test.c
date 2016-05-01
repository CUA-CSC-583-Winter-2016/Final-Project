#include <stdio.h>
#include "opengl_window.h"
#include "GL/glew.h"
#include <stdlib.h>
#include <stdint.h>
#include <libfreenect.h>
#include "head_tracker.h"
#include "kinect_interface.h"

//##############################################################################
// PLANE
//##############################################################################
GLuint plane_prog;
GLuint plane_tex;
GLfloat plane_vert[4][2] = {
  {-1.0,-1.0},{-1.0,1.0},{1.0,-1.0},{1.0,1.0}
};
GLuint plane_VBO;
GLuint plane_VAO;

  const char * plane_vert_shader =
"#version 330 core\n\
in vec2 v_coord;\n\
out vec2 t_coord;\n\
\n\
void main(void) {\n\
  gl_Position = vec4(v_coord, 0.0, 1.0);\n\
  t_coord = vec2(1.0 + v_coord.x,1.0 - +v_coord.y) / 2.0;\n\
}";

  const char * plane_frag_shader =
"#version 330 core\n\
in vec2 t_coord;\n\
uniform sampler2D tex;\n\
\n\
void main(void) {\n\
  gl_FragColor = vec4(vec3(1.0-texture2D(tex,t_coord).r*32),1.0);\n\
}";

void setup_plane() {
  // shaders
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vs,1,&plane_vert_shader,0);
  glCompileShader(vs);
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(plane_prog, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    printf("%s\n",infoLog);
  } else {
    printf("Vertex shader compiled successfully\n");
  }
  glShaderSource(fs,1,&plane_frag_shader,0);
  glGetShaderInfoLog(fs, 512, NULL, infoLog);
  glCompileShader(fs);
  glGetShaderiv(plane_prog, GL_COMPILE_STATUS, &success);
  if(!success) {
    printf("%s\n",infoLog);
  } else {
    printf("Fragment shader compiled successfully\n");
  }
  plane_prog = glCreateProgram();
  glAttachShader(plane_prog,vs);
  glAttachShader(plane_prog,fs);
  glLinkProgram(plane_prog);
  glGetProgramiv(plane_prog, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(plane_prog, 512, NULL, infoLog);
    printf("Failure\n%s\n",infoLog);
  } else {
   printf("Program linked successfully\n");
  }
  glDeleteShader(vs);
  glDeleteShader(fs);

  glUseProgram(plane_prog);
  glGenBuffers(1,&plane_VBO);
  glBindBuffer(GL_ARRAY_BUFFER,plane_VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*2*4,plane_vert,GL_STATIC_DRAW);
  glGenVertexArrays(1,&plane_VAO);
  glBindVertexArray(plane_VAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(glGetAttribLocation(plane_prog,"v_coord"),2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*2,(GLvoid *) 0);
  glBindVertexArray(0);

  glUniform1i(glGetUniformLocation(plane_prog, "tex"), 0);


  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1,&plane_tex);
  glBindTexture(GL_TEXTURE_2D, plane_tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  uint16_t b[640*480];
  for (int i = 0; i < 640*480; i++) {
    b[i] = rand();
  }

  glTexImage2D(GL_TEXTURE_2D,0,GL_RED,640,480,0,GL_RED,GL_UNSIGNED_SHORT,b);
}

void draw_plane() {
  glUseProgram(plane_prog);
  glBindVertexArray(plane_VAO);
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  glBindVertexArray(0);
  glUseProgram(0);
}

void buffer_depth(uint16_t *depth) {
  glTexImage2D(GL_TEXTURE_2D,0,GL_RED,640,480,0,GL_RED,GL_UNSIGNED_SHORT,depth);
}

//##############################################################################
// CROSSHAIR
//##############################################################################
GLuint ch_prog;
GLfloat ch_vert[4][2] = {
  {0.0,2.0},{0.0,-2.0},{2.0,0.0},{-2.0,0.0}
};
GLuint ch_VBO;
GLuint ch_VAO;

const char * ch_vert_shader =
"#version 330 core\n\
in vec2 v_coord;\n\
uniform vec2 offset;\n\
\n\
void main(void) {\n\
  gl_Position = vec4(v_coord + offset, 0.0, 1.0);\n\
}";

const char * ch_frag_shader =
"#version 330 core\n\
uniform vec4 color;\n\
\n\
void main(void) {\n\
  gl_FragColor = color;\n\
}";

void setup_ch() {
  // shaders
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vs,1,&ch_vert_shader,0);
  glCompileShader(vs);
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(ch_prog, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    printf("%s\n",infoLog);
  } else {
    printf("Vertex shader compiled successfully\n");
  }
  glShaderSource(fs,1,&ch_frag_shader,0);
  glGetShaderInfoLog(fs, 512, NULL, infoLog);
  glCompileShader(fs);
  glGetShaderiv(ch_prog, GL_COMPILE_STATUS, &success);
  if(!success) {
    printf("%s\n",infoLog);
  } else {
    printf("Fragment shader compiled successfully\n");
  }
  ch_prog = glCreateProgram();
  glAttachShader(ch_prog,vs);
  glAttachShader(ch_prog,fs);
  glLinkProgram(ch_prog);
  glGetProgramiv(ch_prog, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ch_prog, 512, NULL, infoLog);
    printf("Failure\n%s\n",infoLog);
  } else {
   printf("Program linked compiled successfully\n");
  }
  glDeleteShader(vs);
  glDeleteShader(fs);

  glUseProgram(ch_prog);
  glGenBuffers(1,&ch_VBO);
  glBindBuffer(GL_ARRAY_BUFFER,ch_VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*2*4,ch_vert,GL_STATIC_DRAW);
  glGenVertexArrays(1,&ch_VAO);
  glBindVertexArray(ch_VAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(glGetAttribLocation(ch_prog,"v_coord"),2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*2,(GLvoid *) 0);

  glUniform4f(glGetUniformLocation(ch_prog, "color"), 1.0,0.0,0.0,1.0);
  glUniform2f(glGetUniformLocation(ch_prog, "offset"), 0.0,0.0);
  glBindVertexArray(0);
  glUseProgram(0);
}

void set_ch_coords(int x, int y) {
  glUseProgram(ch_prog);
  glUniform2f(glGetUniformLocation(ch_prog, "offset"), (GLfloat) x / 640.0 * 2.0 - 1.0, (GLfloat) -y / 480.0 * 2.0 + 1.0);
  glUseProgram(0);
}

void draw_ch() {
  glUseProgram(ch_prog);
  glBindVertexArray(ch_VAO);
  glDrawArrays(GL_LINES,0,4);
  glBindVertexArray(0);
  glUseProgram(0);
}


//##############################################################################
// Main
//##############################################################################

void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp) {
  // Just an empty callback
}

int main(int argc, char* argv[]) {
  //init kinect
  init_kinect();

  //draw
  uint16_t b[640*480],c[640*480];
  create_window();
  setup_plane();
  setup_ch();
  for (int i = 0; i < 300; i++)
    get_depth(b);
  int x=0,y=0;
  uint16_t z=0;
  while(!should_close_window()) {
    get_depth(c);
    buffer_depth(c);
    draw_plane();
    locate_head(b, c, 640, 480, &x, &y, &z);
    set_ch_coords(x,y);
    draw_ch();
    swap_buffers();
  }
  return 0;
  close_window();
  shutdown_kinect();
}
