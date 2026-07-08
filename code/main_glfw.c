//[h] includes
#include "base.h"

//[c] includes
#include "base.c"
#include <GLFW/glfw3.h>

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action,
                       int mods) {}

int main() {
  Arena *permanent_arena = arena_alloc(KB(5));
  Assert(glfwInit());
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(1600, 900, "gloggy", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, glfw_key_callback);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}
