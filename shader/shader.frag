#version 330 core

in vec2 tex_coord;
out vec4 pixel_color;

uniform sampler2D _texture;

void main() {
  pixel_color = texture(_texture, tex_coord);
}
