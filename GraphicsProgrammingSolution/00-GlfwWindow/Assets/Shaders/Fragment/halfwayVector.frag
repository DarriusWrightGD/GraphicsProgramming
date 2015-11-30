#version 450
layout(early_fragment_tests) in;
layout(std140) uniform LightBlock
{
	vec3 position;
	vec3 color;
}light;

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec3 eyePosition;
}fs_in;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec4 specular;
};
uniform Material material;

vec3 ads(vec3 position, vec3 normal)
{
	vec3 lightDir = normalize(light.position - position);
	float lDotN = dot(lightDir, normal);
	vec3 diffuse = light.color * material.diffuse * lDotN;

	vec3 specular = vec3(0.0f);
	if(lDotN > 0)
	{
		vec3 viewerDir = normalize(fs_in.eyePosition - position);
		vec3 halfVector = normalize(viewerDir + lightDir);
		specular = light.color * material.specular.rgb * pow(max(dot(halfVector,normal),0.0f),material.specular.w);
	}

	return material.ambient + diffuse + specular;
}
out vec4 color;
void main()
{
	color = vec4(ads(fs_in.position, fs_in.normal),1.0f);
}