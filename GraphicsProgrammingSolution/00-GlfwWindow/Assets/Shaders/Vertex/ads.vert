#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 uv;

layout(std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;

layout(std140) uniform LightBlock
{
	vec3 position;
	vec3 color;
}light;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec4 specular;
};
uniform Material material;

vec3 phongModel(vec4 position, vec3 normal)
{
	vec3 lightDir = normalize(light.position - vec3(position));
	float lightDotNormal = dot(lightDir,normal);
	vec3 diffuseColor = light.color * material.diffuse * max(lightDotNormal,0.0);
	//vec3 reflectedVector = -lightDir + 2 * lightDotNormal * normal;
	vec3 reflectedVector = reflect(-lightDir,normal);
	vec3 viewer = normalize(-transform.eyePosition);
	vec3 spec = vec3(0.0);

	if(lightDotNormal > 0.0f)
	{
		spec = light.color * vec3(material.specular) * pow(max(dot(viewer,reflectedVector),0.0),material.specular.w);
	}

	return material.ambient + diffuseColor + spec;
}

out VS_OUT
{
	vec3 color;
}vs_out;

uniform mat4 world;

void main()
{	
	vec4 worldPosition = world * vec4(position,1.0f);
	vs_out.color = phongModel(worldPosition, normal);
	gl_Position = transform.projection * transform.view * worldPosition;
}