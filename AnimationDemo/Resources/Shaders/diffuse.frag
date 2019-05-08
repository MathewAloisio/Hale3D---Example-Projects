#version 420 core

layout (location = 0) out vec4 outColor;

in vec2 UV;

uniform vec4 entityColor;

// texture0 - diffuse
uniform sampler2D texture0;

void main() {
	vec4 diffuse = texture(texture0, UV);
	outColor = diffuse * entityColor;
}