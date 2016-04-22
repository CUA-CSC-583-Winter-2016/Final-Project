#include <stdio.h>
#include "opengl_window.h"
#include "opengl_rendering.h"
#include "GL/glew.h"
#include <stdlib.h>
#include <stdint.h>
#include <libfreenect.h>

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
  t_coord = (v_coord + 1.0) / 2.0;\n\
}";

  const char * plane_frag_shader =
"#version 330 core\n\
in vec2 t_coord;\n\
uniform sampler2D tex;\n\
\n\
void main(void) {\n\
  gl_FragColor = vec4(vec3(texture2D(tex,t_coord).r),1.0);\n\
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
   printf("Fragment shader compiled successfully\n");
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

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1,&plane_tex);
  glBindTexture(GL_TEXTURE_2D, plane_tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glUniform1i(glGetUniformLocation(plane_prog, "tex"), 0);
  uint16_t random[640*480];
  for (int i = 0; i < 640*480; i++) {
    random[i] = rand();
  }
  glTexImage2D(GL_TEXTURE_2D,0,GL_RED,640,480,0,GL_RED,GL_UNSIGNED_SHORT,random);
}

void buffer_depth(uint16_t *depth) {
  glActiveTexture(GL_TEXTURE0);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RED,640,480,0,GL_RED,GL_UNSIGNED_SHORT,depth);
}

void draw_plane() {
  glBindVertexArray(plane_VAO);
  glDrawArrays(GL_TRIANGLE_STRIP,0,4);
  glBindVertexArray(plane_VAO);
}


int main(int argc, char* argv[]) {
  freenect_context *f_ctx;
  freenect_device *f_dev;
  freenect_init(&f_ctx,NULL);
  freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_CAMERA));
  if (!freenect_num_devices(f_ctx)) {
    printf("No devices found\n");
    return 1;
  }
  freenect_open_device(f_ctx,&f_dev,0);


  create_window();
  setup_plane();
  while(!should_close_window()) {
    draw_plane();
    swap_buffers();
  }
  return 0;
  close_window();
}
