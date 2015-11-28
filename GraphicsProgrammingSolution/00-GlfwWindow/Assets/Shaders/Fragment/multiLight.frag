#version 450

struct Light
{
	vec3 position;
	vec3 color;
};
uniform Light lights[3];

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec4 specular;
};
uniform Material material;


in VS_OUT
{
	vec3 normal;
	vec3 position;
	vec3 eyePosition;
}fs_in;

vec3 ads(int index)
{
	vec3 lightDir = normalize(lights[index].position - fs_in.position);
	float lDotN = dot(lightDir,fs_in.normal);
	vec3 d = lights[index].color * material.diffuse * max(lDotN, 0.0);
	vec3 viewDir = normalize(fs_in.eyePosition - fs_in.position);
	//vec3 reflectedNormal = -lightDir + 2 * lDotN * normal;
	vec3 reflectedNormal = reflect(-lightDir, fs_in.normal);
	vec3 s = vec3(0.0);

	if(lDotN > 0.0f)
	{
		s = lights[index].color * vec3(material.specular) * pow(max(dot(viewDir,reflectedNormal),0.0),material.specular.w);
	} 
	return d ;
}

out vec4 color;

void main()
{
	for(int i = 0; i < lights.length(); i++)
		color += vec4(ads(i),1.0f);
}