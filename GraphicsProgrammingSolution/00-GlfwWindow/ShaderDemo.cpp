#include "ShaderDemo.h"

static const GLchar * vertexShaderSource[] = {
	"#version 440\n"
	"void main(){\n"
	"const vec4 vertices[3] = vec4[3]\n"
	"(vec4(0.25,-0.25,0.5,1.0),\n"
	"vec4(-0.25,-0.25,0.5,1.0),\n"
	"vec4(0.25,0.25,0.5,1.0));\n"
	"gl_Position = vertices[gl_VertexID];\n"
	"}\n"
};

static const GLchar * fragmentShaderSource[] = {
	"#version 440\n"
	"out vec4 color;\n"
	"void main(){\n"
	"color = vec4(0.2,0.8,1.0,1.0);\n"
	"}\n"
};

ShaderDemo::ShaderDemo()
{
}

ShaderDemo::~ShaderDemo()
{
}

#include <iostream>
using std::cout;
using std::endl;
void ShaderDemo::BuildProgram()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	GLint logSize = 0;
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

		for (auto c : errorLog)
		{
			cout << c;
		}
		cout << endl;

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(vertexShader); // Don't leak the shader.
	}
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logSize);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);
		for (auto c : errorLog)
		{
			cout << c;
		}
		cout << endl;

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(fragmentShader); // Don't leak the shader.
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		for (auto c : infoLog)
		{
			cout << c;
		}
		cout<<endl;
		//We don't need the program anymore.
		glDeleteProgram(program);
		//Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//Use the infoLog as you see fit.

		//In this simple program, we'll just leave
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderDemo::Initialize()
{
	SetTitle("ShaderDemo");

	BuildProgram();
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glPointSize(40.0f);
}

void ShaderDemo::Shutdown()
{
	glDeleteVertexArrays(1, &vertexArray);
}

void ShaderDemo::Update()
{
}

void ShaderDemo::Render()
{
	const GLfloat color[] = { static_cast<GLfloat>(cos(time)) * 0.6f,static_cast<GLfloat>(sin(time)) * 0.3f,0.3f,1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	//glDrawArrays(GL_POINTS, 0, 1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
