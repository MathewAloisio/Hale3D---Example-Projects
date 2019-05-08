#version 420 core

layout (location = 0) out vec4 outColor;

in vec2 UV;

uniform vec4 color;
uniform bool useTexture;
uniform sampler2D texture0; // texture0 - image.

void main() {
	if (useTexture) {
		outColor = mix(texture(texture0, UV), color, 0.5f);
	}
	else { outColor = color; }
}