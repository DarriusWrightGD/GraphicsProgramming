#version 450

layout (binding = 0) uniform sampler2D tex;

layout (std140) uniform TransformBlock
{
	mat4 view;
	mat4 projection;
	vec3 eyePosition;
}transform;

layout (std140) uniform LightBlock
{
	vec3 position;
	vec3 color;
}light;

in VS_OUT
{
	vec3 position;
	vec3 normal;
	vec2 uv;
	vec4 projTexCoord;
}fs_in;

struct Material
{
	vec3 diffuse;
};

uniform Material material;

vec3 diffuseLight(vec3 position, vec3 normal)
{
	vec3 lightView = (transform.view * vec4(light.position,1.0)).xyz;
	float lDotN = max(dot(normalize(lightView - position),normalize(normal)),0.0f ) ;
	return light.color * material.diffuse * lDotN;
}
out vec4 color;
void main()
{
	vec3 diffuse = diffuseLight(fs_in.position, fs_in.normal);
	vec4 projColor = vec4(0.0);
	if(fs_in.projTexCoord.z > 0.0)
	{
		projColor = textureProj(tex,fs_in.projTexCoord);
	}

	color = vec4(diffuse,1.0f) + projColor * 0.5f;
}