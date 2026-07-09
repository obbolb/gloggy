//  TODO: make *_inc files

//[h] includes
#include "base.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//[c] includes
#include "base.c"
#if OS_LINUX
#include "base_linux.c"
#endif
#include "r_gl.c"
#include "third_party/glad/src/gl.c"

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  log_debug("%c", key);
}

int main() {
  Arena* permanent_arena = arena_alloc(MB(32));
  Assert(glfwInit());
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(1600, 900, "gloggy", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, glfw_key_callback);

  Assert(r_gl_load_func((GLADloadfunc)glfwGetProcAddress));

  glViewport(0, 0, 1600, 900);

  GLfloat vertices[] = {-0.5, -0.5, 0, 1, 0, 0, 0.5, -0.5, 0, 0, 1, 0, 0, 0.5, 0, 0, 0, 1};

  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  GLuint program = r_gl_create_program(permanent_arena, "code/shader.vert", "code/shader.frag");

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
  }
}
