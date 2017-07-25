#version 330

in vec2 vFragTCoord;

out vec4 vOutColor;

uniform sampler2D texBase;

void main() {
	vOutColor = texture(texBase, vFragTCoord);
}