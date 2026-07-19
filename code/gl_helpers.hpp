#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"

namespace gl {

b8 load_func(GLADloadfunc func) {
  return gladLoadGL(func);
}

class Shader {
public:
  Shader() = delete;
  Shader(Arena* arena, const char* vert_shader_path, const char* frag_shader_path);

  void set_mat4_uniform(const char* param, f32* mat);
  void use();

private:
  GLuint m_id;
};

Shader::Shader(Arena* arena, const char* vert_shader_path, const char* frag_shader_path) {
  TempArena temp = temp_arena_start(arena);

  m_id = glCreateProgram();

  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

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

  glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint size;
    glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &size);
    GLchar* buf = arena_push_array(temp.arena, GLchar, size);
    glGetShaderInfoLog(frag, size, 0, buf);
    log_error("frag : %s", buf);
  }

  glAttachShader(m_id, vert);
  glAttachShader(m_id, frag);
  glLinkProgram(m_id);

  glDeleteShader(vert);
  glDeleteShader(frag);

  temp_arena_end(temp);
}

void Shader::set_mat4_uniform(const char* param, f32* mat) {
  GLint location = glGetUniformLocation(m_id, param);
  glUniformMatrix4fv(location, 1, false, mat);
}

void Shader::use() {
  glUseProgram(m_id);
}

GLuint create_texture(const char* img_path) {
  GLuint tex;
  i32 width, height;
  u8* img = stbi_load(img_path, &width, &height, nullptr, 4);
  Assert(img);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(img);
  glBindTexture(GL_TEXTURE_2D, 0);
  return tex;
}
} // namespace gl
