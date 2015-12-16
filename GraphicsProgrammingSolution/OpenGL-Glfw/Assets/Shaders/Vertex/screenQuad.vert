#version 450

//out VS_OUT
//{
//	vec2 uv;
//}vs_out.uv;
vec4 corners = vec4(1,1,1,1);

vec2 positions [6] = {
	vec2(-1,1* corner.x),
	vec2(1,1),
	vec2(-1,-1),
	vec2(-1,-1),
	vec2(1,1),
	vec2(1,-1)
};


void main()
{
	//vs_out.uv = uv;
	gl_Position = vec4(positions[gl_VertexID],0.1f,1.0f);
}