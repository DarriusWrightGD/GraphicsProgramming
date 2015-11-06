#include "ShaderPipelineDemo.h"
int main()
{
	WindowInterface * window = new ShaderPipelineDemo();
	int executeValue = window->Execute();
	delete window;
	return executeValue;
}