#version 450

layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2D normalMap;
layout (binding = 2) uniform sampler2D occulsionMap;

layout (std140) uniform LightBlock
{
    vec3 position;
    vec3 color;
}
light;

struct Material
{
    vec3 ambient;
    vec4 specular;
};

uniform Material material;

layout (std140) uniform TransformBlock
{
    mat4 view;
    mat4 projection;
    vec3 eyePosition;
}transform;

in VS_OUT
{
    mat3 toObjectLocal;
    vec3 position;
    vec3 normal;
    vec2 uv;
    vec3 tangent;
}fs_in;

out vec4 color;

vec3 ads(vec3 lightDir, vec3 viewDir, vec3 normal, vec3 diffuse)
{
    float lDotN = max(dot(lightDir, normal), 0.0);
	vec3 reflectedVec = reflect(-lightDir, normal);
	vec3 specular = material.specular.xyz * pow(max(dot(reflectedVec,viewDir),0.0),material.specular.w);
    return  light.color * (material.ambient + (diffuse * lDotN)  + specular);
}


void main()
{
    vec3 lightDir = normalize(fs_in.toObjectLocal*(light.position - fs_in.position));
    vec3 viewDir = normalize(fs_in.toObjectLocal * (transform.eyePosition - fs_in.position));
    vec3 normal = (2.0* texture(normalMap,fs_in.uv) - 1.0).xyz;
    vec3 diffuse = texture(diffuseMap, fs_in.uv).xyz;
    color = vec4(ads(lightDir, viewDir, normal, diffuse),1.0);
    //color = vec4(fs_in.tangent,1.0);
}