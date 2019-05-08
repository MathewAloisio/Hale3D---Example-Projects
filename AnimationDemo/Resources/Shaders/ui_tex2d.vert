#version 420 core

layout (location = 0) in vec2 vertexPositions;
layout (location = 1) in vec2 vertexCoords;

uniform float rotation;
uniform vec2 scale;
uniform vec2 scaledCenter;

out vec2 UV;

mat4 translate2D(vec2 pVec2){
    return mat4(
        vec4(1.0f, 		0.0f,  	 0.0f, 0.0f),
        vec4(0.0f, 		1.0f,  	 0.0f, 0.0f),
        vec4(0.0f, 		0.0f,  	 1.0f, 0.0f),
        vec4(pVec2.x,   pVec2.y, 0.0f, 1.0f)
    );
}

mat4 rotateZ(float pRotation){
    return mat4(
        vec4(cos(pRotation), -sin(pRotation), 0.0f, 0.0f),
        vec4(sin(pRotation), cos(pRotation),  0.0f, 0.0f),
        vec4(0.0f, 			 0.0f, 			  1.0f, 0.0f),
        vec4(0.0f, 			 0.0f, 			  0.0f, 1.0f)
	);
}

void main() 
{
	if (rotation == 0.0f) {
		gl_Position = vec4(scale * vertexPositions.xy, 0.0f, 1.0f);
	}
	else {
		gl_Position = translate2D(scaledCenter) * rotateZ(rotation) * translate2D(-scaledCenter) * vec4(scale * vertexPositions.xy, 0.0f, 1.0f);
	}
	UV = vertexCoords;
}
