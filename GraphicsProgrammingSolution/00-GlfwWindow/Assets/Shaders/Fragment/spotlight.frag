#version 450

layout (std140) uniform LightBlock
{
	vec3 color;
	vec3 position;
	vec3 direction;
	float exponent;
	float cutOffAngle;
}light;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec4 specular;
};

uniform Material material;

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec3 eyePosition;
}fs_in;

vec3 ads(vec3 position, vec3 normal)
{
	vec3 lightDir = normalize(light.position - position);
	float angle = acos(dot(-lightDir,light.direction));
	float cutoff = radians(clamp(light.cutOffAngle,0.0f,90.0f));
	vec3 color = material.ambient;

	if(angle < cutoff)
	{
		float spotFactor = pow(dot(-lightDir,light.direction),light.exponent);
		vec3 viewDir = normalize(fs_in.eyePosition - position);
		vec3 halfDir = normalize(viewDir + lightDir);
		vec3 diffuse = light.color * material.diffuse * max(dot(lightDir, normal),0.0f);
		vec3 specular = light.color * material.specular.xyz * pow(max(dot(halfDir,normal),0.0f),material.specular.w);
		color += spotFactor* (diffuse + specular);
		//color = vec3(1.0,0.0,0.0);//+= spotFactor * light.color * diffuse * specular;
	}

	return color;
}

out vec4 color;

void main()
{
	color = vec4(ads(fs_in.position, normalize(fs_in.normal)),1.0f);
}