#define GLM_FORCE_RADIANS
#include <Demos\FragCoordDemo.h>
#include <Demos\ShaderColorDemo.h>
#include <Demos\BufferDemo.h>
#include <Demos\VertexBufferDemo.h>
#include <Demos\LoadingObjDemo.h>
#include <memory>
#include<ServiceLocator.h>
using std::unique_ptr;

int main()
{
	auto window = unique_ptr<WindowInterface>(new LoadingObjDemo());
	return window->Execute();
}