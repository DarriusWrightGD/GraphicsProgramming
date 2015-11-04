#include "ShaderDemo.h"
int main()
{
	WindowInterface * window = new ShaderDemo();
	int executeValue = window->Execute();
	delete window;
	return executeValue;
}