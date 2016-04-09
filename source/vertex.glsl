#version 330 core
layout (location = 0) in vec3 position;
uniform mat4 m = mat4(
  0.5,0.0,0.0,0.04,
  0.0,0.5,0.0,0.0,
  0.0,0.0,0.5,0.2,
  0.0,0.0,0.0,1.0
);
void main() {
  gl_Position = m * vec4(position.x, position.y, position.z, 1.0);
}
