#version 450 core

layout (early_fragment_tests) in;

out vec4 fsColor;

void main()
{
	fsColor = vec4(0.4,0.7,0.4,1.0);
}