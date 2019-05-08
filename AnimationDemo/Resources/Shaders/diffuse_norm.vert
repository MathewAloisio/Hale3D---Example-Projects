#version 420 core

layout (location = 0) in vec3 vertexPositions;
layout (location = 1) in vec2 vertexUVCoords;
layout (location = 2) in vec3 vertexNormals;
layout (location = 3) in vec3 vertexTangents;
layout (location = 4) in vec3 vertexBitangents;

out vec2 UV;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

void main() {
	gl_Position = cameraMatrix * modelMatrix * vec4(vertexPositions, 1.0f);
	UV = vertexUVCoords;
}
