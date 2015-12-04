#version 450 core

layout(early_fragment_tests) in;

out vec4 color;

void main()
{
	color = vec4(cos(0.25*gl_FragCoord.x),sin(0.3*gl_FragCoord.x),cos(0.65*gl_FragCoord.x),1.0);
}