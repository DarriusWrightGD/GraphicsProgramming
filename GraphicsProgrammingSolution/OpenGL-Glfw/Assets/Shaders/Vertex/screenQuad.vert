#version 450

out VS_OUT
{
	vec2 uv;
}vs_out;
uniform vec4 offsets = vec4(0.0,1.0,0.0,1.0); // left right top bottom
uniform float depth = 0.0f;

float convert(float percent)
{
	return 2 * percent - 1;
}

vec4 getVertex(int index, vec4 clampedOffsets)
{
	vec4 position = vec4(0.0f);
	switch(index)
	{
		case 0://left
		position = vec4(vec2(convert(clampedOffsets.x), convert(1.0f-clampedOffsets.w)),
		vec2(0,0) ) ;
		break;
		case 1:
		case 4:
		position = vec4(vec2(convert(clampedOffsets.y), convert(1.0f-clampedOffsets.w)),
		vec2(1,0) ) ;
		break; 
		case 2:
		case 3:
		position =  vec4(convert(clampedOffsets.x), convert(1.0f-clampedOffsets.z),
		vec2(0,1) ) ;
		break; 
		case 5:
		position =  vec4(convert(clampedOffsets.y), convert(1.0f-clampedOffsets.z),
		vec2(1,1) ) ;
		break;
	}

	return position;
}

void main()
{
	vec4 clampedOffsets = clamp(offsets,0.0f,1.0f);
	float clampedDepth = clamp(depth,0.0f,0.99f);
	vec4 vertex = getVertex(gl_VertexID, clampedOffsets);
	vs_out.uv = vertex.zw;
	gl_Position = vec4(vertex.xy,clampedDepth,1.0f);
}