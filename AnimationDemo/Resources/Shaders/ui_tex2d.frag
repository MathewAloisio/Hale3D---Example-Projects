#version 420 core

layout (location = 0) out vec4 outColor;

in vec2 UV;

uniform vec4 color;

// texture0 - font texture atlas.
uniform sampler2D texture0;

uniform bool useTexture;
uniform sampler2D texture1; // texture1 - image.

void main() {
	if (useTexture) {
		outColor = mix(texture(texture1, UV), color, 0.5f) * vec4(1.0f, 1.0f, 1.0f, texture(texture0, UV).r);
	}
	else { outColor = color * vec4(1.0f, 1.0f, 1.0f, texture(texture0, UV).r); }
}