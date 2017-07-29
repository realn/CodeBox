#version 330

in vec3 vInVertex;
in vec2 vInTCoord;

out vec2 vFragTCoord;

uniform mat4 mTransform;

void main() {
	vFragTCoord = vInTCoord;
	gl_Position = mTransform * vec4(vInVertex, 1.0f);
}
