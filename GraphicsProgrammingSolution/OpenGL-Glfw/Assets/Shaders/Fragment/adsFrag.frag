#version 450
layout(early_fragment_tests) in;
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec4 specular;
};

uniform Material material;

layout(std140) uniform LightBlock
{
	vec3 position;
	vec3 color;
}light;


in VS_OUT
{
	vec3 normal;
	vec3 position;
	vec3 eyePosition;
}fs_in;


layout(std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;

vec3 phongModel(vec3 position, vec3 normal)
{
	vec3 lightDir = normalize((transform.view * vec4(light.position,1.0)).xyz - position);
	float lightDotNormal = dot(lightDir,normal);
	vec3 diffuseColor = light.color * material.diffuse * max(lightDotNormal,0.0);
	//vec3 reflectedVector = -lightDir + 2 * lightDotNormal * normal;
	vec3 reflectedVector = reflect(-lightDir,normal);
	vec3 viewer = normalize(-fs_in.position);
	vec3 spec = vec3(0.0);

	if(lightDotNormal > 0.0f)
	{
		spec = light.color * vec3(material.specular) * pow(max(dot(viewer,reflectedVector),0.0),material.specular.w);
	}

	return material.ambient + diffuseColor + spec;
}


out vec4 color;
void main()
{
	color = vec4(phongModel(fs_in.position, normalize(fs_in.normal)),1.0);
}