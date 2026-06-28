#version 330 core
out vec4 frag_color;
in vec3 out_pos;
in vec2 out_tex_coord;
in vec3 out_color;
uniform sampler2D ourTexture;

void main() {
    frag_color=texture(ourTexture, out_tex_coord) * vec4(out_color, 1);
}
