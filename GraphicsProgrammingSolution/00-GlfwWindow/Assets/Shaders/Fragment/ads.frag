#version 450
layout (early_fragment_tests) in;

in VS_OUT
{
	vec3 color;
}fs_in;

out vec4 color;
void main()
{
	color = vec4(fs_in.color,1.0);
}