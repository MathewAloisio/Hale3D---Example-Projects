#version 420 core

layout (location = 0) out vec4 outColor;

in vec2 UV;

uniform float radius;
uniform float borderPctRadius;
uniform vec2 position;
uniform vec4 color;
uniform bool useTexture;
uniform sampler2D texture0; // texture0 - image.

float circle(in vec2 pUV, in float pInnerRadius, in float pUVLength) {
	if (pUVLength > radius) discard; // Although anti-aliasing would handle it, this is a less expensive check.
	if (borderPctRadius < 1.0f && pUVLength < pInnerRadius) discard;
	float pctRadius = radius * 0.01f;
	return 100.0f - smoothstep(radius - pctRadius, radius + pctRadius, dot(pUV, pUV));
}

float antialias(in vec2 pUV, in float pInnerRadius, in float pUVLength) {
	const float border = 1.0f;
	float uvDist = radius - pUVLength; // Outer-edge check. (abs() not needed as pixel is discarded earlier if pUVLength > radius.)
	if (uvDist > border) {
		uvDist = abs(pInnerRadius - pUVLength); // Inner-edge check.
		if (uvDist < border) {
			return uvDist / border;
		}
		else { return 1.0f; }
	}
	else { return uvDist / border; }
}

void main() {
	// Calculate fragment distance from center. along with this length & the inner radius.
	vec2 uv = gl_FragCoord.xy - position;
	float uvLength = length(uv);
	float innerRadius = radius - (radius * borderPctRadius);
	
	// Output the final color.
	if (useTexture) {
		vec4 mixedColor = mix(texture(texture0, UV), color, 0.5f);
		outColor = vec4(mixedColor.xyz * vec3(circle(uv, innerRadius, uvLength)), antialias(uv, innerRadius, uvLength) * mixedColor.w);
	}
	else { outColor = vec4(color.xyz * vec3(circle(uv, innerRadius, uvLength)), antialias(uv, innerRadius, uvLength) * color.w); }
}