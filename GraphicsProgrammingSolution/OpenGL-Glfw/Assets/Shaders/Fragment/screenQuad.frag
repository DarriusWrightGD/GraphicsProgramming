#version 450 

//layout (binding = 0) uniform sampler2D image;

//in VS_OUT
//{
//	vec2 uv;
//}fs_in;

out vec4 color;

void main()
{
	color = vec4(0.2,0.9,0.6,1.0f);// texture(image,fs_in.uv);
}