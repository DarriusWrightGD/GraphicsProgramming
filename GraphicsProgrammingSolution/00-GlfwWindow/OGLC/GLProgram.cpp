#include "GLProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;


GLProgram::GLProgram()
{
}


GLProgram::~GLProgram()
{
	Delete();
}

void GLProgram::AddShaderSource(ShaderType shaderType, const char * source)
{
	if (!initailzed)
	{
		Initialize();
	}

	auto shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	auto success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	auto logSize = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
	if (success == GL_FALSE)
	{
		auto maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		auto errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);
		cout << errorLog << endl;
		glDeleteShader(shader);
		delete errorLog;
	}
	shaders.push_back(shader);
}

void GLProgram::AddShaderSource(ShaderType shaderType, std::string source)
{
	AddShaderSource(shaderType, source.c_str());
}

void GLProgram::Initialize()
{
	program = glCreateProgram();
	initailzed = true;
}

void GLProgram::AddShaderFile(ShaderType shaderType, const char * file)
{
	ifstream stream(file);
	stringstream buffer;
	buffer << stream.rdbuf();
	AddShaderSource(shaderType, buffer.str());
}

void GLProgram::AddShaderFile(ShaderType shaderType, std::string file)
{
	AddShaderFile(shaderType, file.c_str());
}

void GLProgram::AddUniform(const char * name, float * value)
{
}

void GLProgram::AddUniform(std::string name, float * value)
{
}

void GLProgram::Build()
{
	for (auto shader : shaders)
	{
		glAttachShader(program, shader);
	}
	glLinkProgram(program);
	auto isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE)
	{
		auto maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		auto infoLog = new GLchar[maxLength];
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		cout << infoLog << endl;
		delete infoLog;
		glDeleteProgram(program);
	}
	DeleteShaders();
}

void GLProgram::Use()
{
	glUseProgram(program);
}

void GLProgram::DeleteShaders()
{
	for (auto shader : shaders)
	{
		glDeleteShader(shader);
	}
}

void GLProgram::Delete()
{
	glDeleteProgram(program);
	DeleteShaders();
}

GLuint GLProgram::GetHandle() const
{
	return program;
}
