#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//standard method 
//layout(std140, binding = 0) uniform TransformBlock
//{

//}transform;



out VS_OUT{
	vec4 color;
}vs_out;

void main()
{
	vs_out.color = vec4(position,1.0);
	//gl_Position = transform.perspective * transform.view * model * vec4(position,1.0);
	gl_Position = projection * view * model * vec4(position,1.0);
}