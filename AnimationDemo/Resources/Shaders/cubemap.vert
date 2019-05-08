#version 420 core

layout (location = 0) in vec3 vertexPositions;

out vec3 direction;

uniform mat4 cameraMatrix;

void main() {
	gl_Position = cameraMatrix * vec4(vertexPositions, 1.0f);
	direction = vertexPositions;
}
