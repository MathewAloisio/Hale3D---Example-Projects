#version 420 core

layout (location = 0) out vec4 outColor;

in vec2 UV;

uniform vec4 entityColor;

// texture0 - diffuse | texture2 - normal
uniform sampler2D texture0;
uniform sampler2D texture2;

void main() {
	vec4 diffuse = texture(texture0, UV);
	vec4 normal = texture(texture2, UV);
	outColor = diffuse * entityColor;
}