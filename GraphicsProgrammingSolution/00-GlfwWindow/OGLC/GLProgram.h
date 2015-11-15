#pragma once
#include <GL\gl_core_4_5.h>
#include <string>
#include <vector>
#include <unordered_map>

enum class ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
	Compute = GL_COMPUTE_SHADER,
	TessellationControl = GL_TESS_CONTROL_SHADER,
	TessellationEvaluation = GL_TESS_EVALUATION_SHADER,
	Geometry = GL_GEOMETRY_SHADER,
};

enum class UniformType
{
	INTEGER,
	BOOL,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	MAT3,
	MAT4,
};

struct Uniform
{
	UniformType type;
	float * value;
};

struct UniformBufferParameter
{
	std::string name;
	float * value;
	size_t size;
};

class UniformBufferBlock
{
public:
	UniformBufferBlock(std::string name, std::vector<UniformBufferParameter> parameters) :
		name(name), parameters(parameters)
	{

	}
	UniformBufferBlock(const char * name, std::vector<UniformBufferParameter> parameters) :
		name(name), parameters(parameters)
	{

	}

	std::string name;
	std::vector<UniformBufferParameter> parameters;
};

struct UniformValue
{
	size_t size;
	float * value;
};

struct UniformBlockValue
{
	std::vector<GLint> offsets;
	std::vector<UniformValue> values;
	GLuint buffer;
	GLuint location;
	GLint blockSize;
};

class GLProgram
{
public:
	GLProgram();
	~GLProgram();
	void AddShaderSource(ShaderType shaderType, const char * source);
	void AddShaderSource(ShaderType shaderType, std::string source);
	void AddShaderFile(ShaderType shaderType, const char * file);
	void AddShaderFile(ShaderType shaderType, std::string file);
	void AddUniform(const char * name, float * value, UniformType type);
	void AddUniform(std::string name, float * value, UniformType type);
	void AddUniformBlock(UniformBufferBlock uniformBlock);
	void UpdateUniformBlock(std::string name);
	void Update();
	void Build();
	void Use();
	void Delete();
	void Initialize();
	
	GLuint GetHandle()const;
private:
	void UpdateUniform(GLint location, Uniform uniform);
	GLint GetUniformLocation(const char * name);
	bool initailzed = false;
	void DeleteShaders();
	void DeleteUniformBuffers();
	std::vector<GLuint> shaders;
	std::unordered_map<GLint, Uniform> uniforms;
	std::unordered_map<std::string, UniformBlockValue> uniformBlocks;
	GLuint program;
};

