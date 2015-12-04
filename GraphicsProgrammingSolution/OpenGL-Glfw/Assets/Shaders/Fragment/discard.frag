#version 450

layout(early_fragment_tests) in;

in VS_OUT
{
	vec3 frontColor;
	vec3 backColor;
	vec2 uv;
}fs_in;

out vec4 color;
void main()
{
	const float scale = 1.0;
	bvec2 toDiscard = greaterThan(fract(fs_in.uv * scale), vec2(0.2,0.2));

	if(all(toDiscard))
		discard;

	color = (gl_FrontFacing) ? vec4(fs_in.frontColor,1.0) : vec4(fs_in.backColor,1.0);
}