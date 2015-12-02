#version 450

layout (early_fragment_tests) in;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec4 specular;
};

uniform Material material;

layout(std140) uniform LightBlock
{
	vec3 direction;
	vec3 color;
}light;


in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec3 eyePosition;
}fs_in;

vec3 ads(vec3 position,vec3 normal)
{
	vec3 lightDir = normalize(-light.direction);
	float lDotN = dot(lightDir,normal);
	vec3 diffuse = light.color * material.diffuse * max(lDotN,0.0f);

	vec3 specular = vec3(0.0f);
	
	if(lDotN > 0.0f)
	{
		vec3 viewDir = normalize(fs_in.eyePosition - position);
		vec3 reflectDir = reflect(-lightDir, normal);
		specular = light.color * material.specular.xyz * pow(max(dot(viewDir,reflectDir),0.0f),material.specular.w);
	}

	return material.ambient + diffuse + specular;
}

out vec4 color;

void main()
{
	color = vec4(ads(fs_in.position,normalize(fs_in.normal)),1.0f);
}