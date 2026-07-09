#include "base.h"
#include <glad/gl.h>

b8 r_gl_load_func(GLADloadfunc func) {
  return gladLoadGL(func);
}

GLuint r_gl_create_program(Arena* arena, const char* vert_shader_path,
                           const char* frag_shader_path) {

  TempArena temp = temp_arena_start(arena);

  GLuint program = glCreateProgram();
  GLuint vert    = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag    = glCreateShader(GL_FRAGMENT_SHADER);

  const GLchar* vert_src = (GLchar*)read_file(temp.arena, vert_shader_path, 0, true);
  const GLchar* frag_src = (GLchar*)read_file(temp.arena, frag_shader_path, 0, true);

  glShaderSource(vert, 1, &vert_src, 0);
  glShaderSource(frag, 1, &frag_src, 0);

  glCompileShader(vert);
  glCompileShader(frag);

  // check shader compilation errs
  GLint success;
  glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint size;
    glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &size);
    GLchar* buf = arena_push_array(temp.arena, GLchar, size);
    glGetShaderInfoLog(vert, size, 0, buf);
    log_error("vert : %s", buf);
  }

  if (!success) {
    GLint size;
    glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &size);
    GLchar* buf = arena_push_array(temp.arena, GLchar, size);
    glGetShaderInfoLog(frag, size, 0, buf);
    log_error("frag : %s", buf);
  }

  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);

  temp_arena_end(temp);

  return program;
}
