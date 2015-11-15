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

	auto shader = glCreateShader(static_cast<GLenum>(shaderType));
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

void GLProgram::AddUniform(const char * name, float * value, UniformType type)
{
	auto location = GetUniformLocation(name);
	if (location != -1)
	{
		uniforms.insert({ location ,{type,value} });
	}
}

void GLProgram::AddUniform(std::string name, float * value, UniformType type)
{
	AddUniform(name.c_str(), value, type);
}

void GLProgram::AddUniformBlock(UniformBufferBlock uniformBlock)
{
	auto uniformIndex = glGetUniformBlockIndex(GetHandle(), uniformBlock.name.c_str());
	if (uniformIndex != MAXUINT32)
	{
		GLint uniformBlockSize;
		glGetActiveUniformBlockiv(GetHandle(), uniformIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
		auto uniformBufferData = new GLubyte[uniformBlockSize];
		std::vector<const GLchar*>names;
		auto numParams = uniformBlock.parameters.size();
		names.reserve(numParams);
		UniformBlockValue blockValue;
		blockValue.location = uniformIndex;
		blockValue.blockSize = uniformBlockSize;
		blockValue.offsets.resize(numParams);
		blockValue.values.reserve(numParams);

		for (const auto & param : uniformBlock.parameters)
		{
			names.push_back(param.name.c_str());
			blockValue.values.push_back({param.size, param.value});
		}
		std::vector<GLuint> indices;
		indices.resize(numParams);
		glGetUniformIndices(GetHandle(), numParams, &names[0], &indices[0]);
		glGetActiveUniformsiv(GetHandle(), numParams, &indices[0], GL_UNIFORM_OFFSET, &blockValue.offsets[0]);

		for (auto param = 0u; param < numParams; param++)
		{
			memcpy(uniformBufferData + blockValue.offsets[param], blockValue.values[param].value, blockValue.values[param].size);
		}


		glCreateBuffers(1, &blockValue.buffer);
		glBindBuffer(GL_UNIFORM_BUFFER, blockValue.buffer);
		glBufferData(GL_UNIFORM_BUFFER, uniformBlockSize, uniformBufferData, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, blockValue.buffer);
		uniformBlocks.insert({ uniformBlock.name.c_str(),blockValue });
		delete [] uniformBufferData;
	}
}

void GLProgram::UpdateUniformBlock(std::string name)
{
	auto uniformBlockIter = uniformBlocks.find(name);
	if (uniformBlockIter != uniformBlocks.end())
	{
		const auto & uniformBlockValue = uniformBlockIter->second;
		auto uniformBufferData = new GLubyte[uniformBlockValue.blockSize];
		for (auto param = 0u; param < uniformBlockValue.offsets.size(); param++)
		{
			memcpy(uniformBufferData + uniformBlockValue.offsets[param], uniformBlockValue.values[param].value, uniformBlockValue.values[param].size);
		}
		glBindBuffer(GL_UNIFORM_BUFFER, uniformBlockValue.buffer);
		glBufferData(GL_UNIFORM_BUFFER, uniformBlockValue.blockSize, uniformBufferData, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBlockValue.buffer);
		delete[] uniformBufferData;
	}
}


void GLProgram::Update()
{
	Use();
	for (auto uniform : uniforms)
	{
		UpdateUniform(uniform.first, uniform.second);
	}
}

void GLProgram::UpdateUniform(GLint location, Uniform uniform )
{
	switch (uniform.type)
	{
	case UniformType::INTEGER:
	case UniformType::BOOL:
		glUniform1i(location,(int)(*uniform.value));
		break;
	case UniformType::FLOAT:
		glUniform1fv(location, 1 , uniform.value);
		break;
	case UniformType::VEC2:
		glUniform2fv(location, 1, uniform.value);
		break;
	case UniformType::VEC3:
		glUniform3fv(location, 1, uniform.value);
		break;
	case UniformType::VEC4:
		glUniform4fv(location, 1, uniform.value);
		break;
	case UniformType::MAT3:
		glUniformMatrix3fv(location, 1,GL_FALSE, uniform.value);
		break;
	case UniformType::MAT4:
		glUniformMatrix4fv(location, 1,GL_FALSE, uniform.value);
		break;
	}
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

void GLProgram::DeleteUniformBuffers()
{
	for (auto uniformBlock : uniformBlocks)
	{
		glDeleteBuffers(1,&uniformBlock.second.buffer);
	}
}

void GLProgram::Delete()
{
	glDeleteProgram(program);
	DeleteShaders();
	DeleteUniformBuffers();
}


GLuint GLProgram::GetHandle() const
{
	return program;
}

GLint GLProgram::GetUniformLocation(const char * name)
{
	return glGetUniformLocation(program,name);
}
