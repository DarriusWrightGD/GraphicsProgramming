#include "ShaderPipelineDemo.h"



ShaderPipelineDemo::ShaderPipelineDemo()
{
}


ShaderPipelineDemo::~ShaderPipelineDemo()
{
}

void ShaderPipelineDemo::Update()
{
}

void ShaderPipelineDemo::Render()
{
	const GLfloat color[] = { static_cast<GLfloat>(cos(time)) * 0.6f,static_cast<GLfloat>(sin(time)) * 0.3f,0.3f,1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	program.Use();
	const GLfloat triColor[] = { static_cast<GLfloat>(sin(time)) * 0.6f,static_cast<GLfloat>(cos(time)) * 0.3f,0.3f,1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glBindVertexArray(vertexArray);
	glVertexAttrib4fv(0, color);
	glDrawArrays(GL_PATCHES, 0, 3);
}

void ShaderPipelineDemo::Initialize()
{
	program.Initialize();
	program.AddShaderFile(Vertex, "Assets/Shaders/Vertex/pipeline.vert");
	program.AddShaderFile(TessellationControl, "Assets/Shaders/Tessellation/pipeline.tc");
	program.AddShaderFile(TessellationEvaluation, "Assets/Shaders/Tessellation/pipeline.te");
	program.AddShaderFile(Geometry, "Assets/Shaders/Geometry/pipeline.geo");
	program.AddShaderFile(Fragment,"Assets/Shaders/Fragment/pipeline.frag");
	program.Build();
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPointSize(10.0f);

}

void ShaderPipelineDemo::Shutdown()
{
	glDeleteVertexArrays(1, &vertexArray);
	program.Delete();
}
