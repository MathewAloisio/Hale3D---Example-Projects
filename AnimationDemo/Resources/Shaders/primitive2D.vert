#version 420 core

layout (location = 0) in vec2 vertexPositions;

uniform vec2 centerPos;

void main() {
	gl_Position = vec4(vertexPositions + centerPos, 0.0f, 1.0f);
}
