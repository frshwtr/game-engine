#version 440

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_textcoord;

out vec4 fs_color;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    fs_color = texture(texture0, vs_textcoord) * texture(texture1, vs_textcoord);
}