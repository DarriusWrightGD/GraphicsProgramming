#version 450 core

out VS_OUT{
	vec4 color;
}vs_out;

void main()
{
	const vec4 vertices[] = vec4[3](
		vec4(0.25,-0.25,0.5,1.0),
		vec4(-0.25,-0.25,0.5,1.0),
		vec4(0.25,0.25,0.5,1.0)
	);

	const vec4 colors[] = vec4[3](
		vec4(1.0,0.0,0.0,1.0),
		vec4(0.0,1.0,0.0,1.0),
		vec4(0.0,0.0,1.0,1.0)
	);

	vs_out.color = colors[gl_VertexID];
	gl_Position = vertices[gl_VertexID];
}