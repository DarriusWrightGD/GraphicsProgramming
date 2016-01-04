#version 450 

layout (binding = 0) uniform sampler2D image;

in VS_OUT
{
	vec2 uv;
}fs_in;

out vec4 color;

void main()
{
	//color = vec4(1,0,0,1);
	color = texture(image,fs_in.uv);
}