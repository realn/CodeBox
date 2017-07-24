#version 330

in vec3 vInVertex;
in vec3 vInInstPos;

uniform mat4 mTransform;

void main() {
	gl_Position = mTransform * vec4(vInVertex + vInInstPos, 1.0f);
}
