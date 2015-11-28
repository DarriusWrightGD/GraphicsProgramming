#version 450
uniform sampler2D texture1;

in VS_OUT
{
	vec2 uv;
}fs_in;

out vec4 color;

void main()
{
	color = texture(texture1,fs_in.uv);
}