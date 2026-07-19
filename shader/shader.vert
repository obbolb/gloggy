#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 tex_coord;

void main() {
  gl_Position = proj * view * model * vec4(a_pos, 1);
  tex_coord = a_texcoord;
}
