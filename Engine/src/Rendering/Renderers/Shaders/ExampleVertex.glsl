#version 410 core

layout (location = 0) in float offset;
layout (location = 1) in vec3  color;
layout (location = 2) in vec2  vertexOffset;

uniform float theta = 0.f;

out vec3 fragColor;

void main()
{
	vec2 pos;
	pos.x = 0.5 * sin(theta - offset);
	pos.y = 0.5 * cos(theta - offset);
	gl_Position = vec4(pos / 4 + vertexOffset, 0.f, 1.f);
	fragColor = color;
}