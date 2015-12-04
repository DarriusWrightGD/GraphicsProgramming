#version 450 core
layout(early_fragment_tests) in;
out vec4 color;

in VS_OUT
{
	vec4 color;
}fs_in;


void main()
{
	color = fs_in.color;
}