#version 450
layout(binding = 0) uniform sampler2D renderTexture;
out vec4 color;

uniform float edgeThreshold = 0.5f;
const vec3 lum = vec3(0.2126,0.7152, 0.0722);

float luminance(vec3 color)
{
	return dot(lum,color);
}

void main()
{
	ivec2 pix = ivec2(gl_FragCoord.xy);
	float s00 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(-1,1)).rgb);
	float s10 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(-1,0)).rgb);
	float s20 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(-1,-1)).rgb);
	float s01 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(0,1)).rgb);
	float s21 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(0,-1)).rgb);
	float s02 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(1,1)).rgb);
	float s12 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(1,0)).rgb);
	float s22 = luminance(texelFetchOffset(renderTexture,pix,0,ivec2(1,-1)).rgb);

	float sx = s00 + 2 * s10 + s20 - (s02 + 2 *s12 + s22);
	float sy = s00 + 2 * s01 + s02 - (s20 + 2 *s21 + s22);

	float g = sx * sx + sy * sy;

	if(g > edgeThreshold)
	{
		color = vec4(1.0);
	}
	else
	{
		color = vec4(0.0, 0.0, 0.0, 1.0);
	}
}