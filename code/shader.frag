#version 330 core

in vec3 export_color;
out vec4 pixel_color;

void main() {
  pixel_color = vec4(export_color, 1);
}
