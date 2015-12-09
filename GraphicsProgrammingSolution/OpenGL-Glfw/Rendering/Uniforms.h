#pragma once
#include <OGLC\GLProgram.h>


struct UniformUpdate
{
	const char * name;
	UniformType type;
	float * value;
};
