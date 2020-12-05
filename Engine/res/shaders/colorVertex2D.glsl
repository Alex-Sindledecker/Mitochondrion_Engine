#version 410 core

layout (location = 0) in vec2 pos;

uniform mat4 projectionView;
uniform mat4 model;
uniform vec4 spriteColor;

out vec4 color;

void main()
{
	gl_Position = projectionView * model * vec4(pos, 0, 1);	

	color = spriteColor;

}