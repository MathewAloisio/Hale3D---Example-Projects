#version 420 core

layout (location = 0) in vec2 vertexPositions;

out vec2 UV;

const vec2 UVArray[4] = vec2[4](
	vec2(1.0f, 1.0f),
	vec2(1.0f, 0.0f),
	vec2(0.0f, 1.0f),
	vec2(0.0f, 0.0f)
);

void main() {
	gl_Position = vec4(vertexPositions, 0.0f, 1.0f);
	UV = UVArray[gl_VertexID];
}
