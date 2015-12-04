#version 450
layout (early_fragment_tests) in;

layout(binding = 0) uniform sampler2D tex;

in VS_OUT
{
	vec3 position;
	vec2 uv;
}fs_in;

out vec4 color;

void main()
{
	vec4 texColor = texture(tex,fs_in.uv);
	if(texColor.a == 0.0f)
	{
		discard;
	}
	color = texColor;
}
