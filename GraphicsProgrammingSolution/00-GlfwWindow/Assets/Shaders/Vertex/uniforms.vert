#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 model;

//standard method 
layout(std140,binding = 0) uniform TransformBlock
{
    mat4 view;
    mat4 projection;
}transform;

out VS_OUT{
    vec4 color;
}vs_out;

void main()
{
    vs_out.color = vec4(normal,1.0);
    gl_Position = transform.projection * transform.view * model * vec4(position,1.0);
}
