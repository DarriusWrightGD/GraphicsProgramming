#version 450

layout(binding = 0) uniform sampler2D fbo;

in VS_OUT
{
	vec2 uv;
}fs_in;

out vec4 color;

void main()
{
	color = texture(fbo, fs_in.uv);
}