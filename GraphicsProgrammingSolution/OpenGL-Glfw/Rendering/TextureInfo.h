#pragma once
#include <GL\gl_core_4_5.h>

enum class TextureWrapType
{
	Default,
	Cubemap,
	Projection,
};


struct TextureInfo
{
	GLuint id;
	GLint type;
	GLuint sampler;
};