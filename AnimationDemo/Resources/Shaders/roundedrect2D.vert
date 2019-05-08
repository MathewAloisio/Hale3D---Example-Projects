#version 420 core

layout (location = 0) in vec2 vertexPositions;
layout (location = 1) in vec2 vertexUVCoords;

out vec2 UV;

uniform vec2 origin;

void main() {
	gl_Position = vec4(origin + vertexPositions, 0.0f, 100.0f);
	UV = vertexUVCoords;
}
