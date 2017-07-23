#version 330

in vec3 vInVertex;

uniform mat4 mTransform;

void main() {
	gl_Position = mTransform * vec4(vInVertex, 1.0f);
}
