#pragma once
#include <GL\glew.h>
#include <string>
#include <vector>

enum ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
	Compute = GL_COMPUTE_SHADER,
	TessellationControl = GL_TESS_CONTROL_SHADER,
	TessellationEvaluation = GL_TESS_EVALUATION_SHADER,
	Geometry = GL_GEOMETRY_SHADER,
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
	void Build();
	void Use();
	void Delete();
	void Initialize();
	
	GLuint GetHandle()const;
private:
	bool initailzed = false;
	void DeleteShaders();
	std::vector<GLuint> shaders;
	GLuint program;
};

