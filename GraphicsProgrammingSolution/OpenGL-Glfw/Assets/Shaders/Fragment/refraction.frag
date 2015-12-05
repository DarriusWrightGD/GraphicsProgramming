#version 450 

layout(binding = 0) uniform samplerCube cubeMap;

in VS_OUT
{
	vec3 refractDir;
	vec3 reflectDir;
}fs_in;

struct Material{
	float eta;
	float reflectionFactor;
};

uniform Material material;


uniform bool drawSkyBox;
out vec4 reflectedColor; 

void main()
{
	 reflectedColor = texture(cubeMap,fs_in.reflectDir);
	 vec4 refractedColor = texture(cubeMap,fs_in.refractDir);
	
	 if(!drawSkyBox)
	 {
		reflectedColor = mix(refractedColor,reflectedColor,material.reflectionFactor);
	 }
}