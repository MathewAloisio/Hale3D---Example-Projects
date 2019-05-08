#version 420 core

layout (location = 0) out vec4 outColor;

in vec2 UV;

uniform vec4 color;
uniform bool useTexture;
uniform sampler2D texture0; // texture0 - image.

//TODO: Antialiasing

void main() {
	// Output the final color.
	if (useTexture) {
		vec4 mixedColor = mix(texture(texture0, UV), color, 0.5f);
		outColor = vec4(mixedColor.xyz, mixedColor.w);
	}
	else { outColor = color; }
}
