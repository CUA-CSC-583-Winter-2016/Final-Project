#version 330 core
layout (location = 0) in vec3 position;
uniform mat4 m;
void main() {
  gl_Position = m * vec4(position, 1.0);
}
