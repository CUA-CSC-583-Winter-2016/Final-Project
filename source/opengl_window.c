#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow *window;

void error_callback(int error, const char* description)
{
    printf("Error: %s\n",description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  glfwSetWindowShouldClose(window, GL_TRUE);
}

int create_window() {
  if (!glfwInit())
    return 1;
  glfwSetErrorCallback(&error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window = glfwCreateWindow(640, 480, "Off-Axis Perspective Box", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSwapInterval(1);// Vsync on.
  glewExperimental = GL_TRUE;
  glewInit(); // HAS TO BE CALLED AFTER THE WINDOW IS CREATED! WHY DID NO ONE TELL ME THIS (0_0)
  return 0;
}

int should_close_window() {
  glfwPollEvents();
  return glfwWindowShouldClose(window);
}

void swap_buffers() {
  glfwSwapBuffers(window);
}

void close_window() {
  glfwDestroyWindow(window);
}
