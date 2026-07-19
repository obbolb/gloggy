////////////////////////////////
// [h] includes
#include "base/base.h"
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

////////////////////////////////
// [hpp] includes
#include "camera.hpp"
#include "gl_helpers.hpp"

////////////////////////////////
// [c] includes
#include "base/base_inc.c"
#include "third_party/glad/src/gl.c"

////////////////////////////////
// globals
Camera g_camera;

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    g_camera.pos[2] += 0.2;
    log_debug("g_camera val: <%f %f %f>", g_camera.pos[0], g_camera.pos[1], g_camera.pos[2]);
  }
  if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    g_camera.pos[2] -= 0.2;
    log_debug("g_camera val: <%f %f %f>", g_camera.pos[0], g_camera.pos[1], g_camera.pos[2]);
  }
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

  Assert(gl::load_func((GLADloadfunc)glfwGetProcAddress));

  glViewport(0, 0, 1600, 900);
  glEnable(GL_DEPTH_TEST);

  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
      1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  -0.5f,
      -0.5f, -0.5f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
      0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  -0.5f, 0.5f,
      0.5f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  -0.5f, -0.5f, -0.5f,
      0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,  0.5f,
      0.5f,  0.5f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 0.0f,
      1.0f,  0.5f,  -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  0.5f,  0.5f,
      0.5f,  1.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
      0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.5f,
      0.5f,  -0.5f, 1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,
      0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f};
  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(GLfloat), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  gl::Shader shader(permanent_arena, "shader/shader.vert", "shader/shader.frag");
  GLuint tex = gl::create_texture("grass.png");

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  mat4 view  = GLM_MAT4_IDENTITY_INIT;
  mat4 proj  = GLM_MAT4_IDENTITY_INIT;

  glm_rotate(model, glm_rad(45), GLM_YUP);
  glm_perspective_default(1600 / 900.0f, proj);

  shader.use(); // redundant
  shader.set_mat4_uniform("model", (float*)model);
  shader.set_mat4_uniform("proj", (float*)proj);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.use();
    g_camera.get_view_matrix(&view);
    shader.set_mat4_uniform("view", (float*)view);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glfwSwapBuffers(window);
  }
}
