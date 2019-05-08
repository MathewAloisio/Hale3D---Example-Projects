#version 420 core

layout (location = 0) out vec4 outColor;

in vec3 direction;

// texture0 - cubemap.
uniform samplerCube texture0;

void main() {
	vec4 diffuse = texture(texture0, direction);
	outColor = diffuse;
}