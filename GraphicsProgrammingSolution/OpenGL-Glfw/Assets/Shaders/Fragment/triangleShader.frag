#version 450 core

layout(early_fragment_tests) in;

out vec4 color;

void main()
{
	color = vec4(0.2,0.8,1.0,1.0);
}