#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUv;

uniform mat4 viewProjection;
uniform mat4 model;

out vec3 normal;
out vec2 uv;
out vec3 color;

void main()
{
	gl_Position = viewProjection * model * vec4(pos, 1.0);
	normal = mat3(transpose(inverse(model))) * vertexNormal;
	uv = vertexUv;
	color = pos;
}