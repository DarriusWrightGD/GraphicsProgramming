#define GLM_FORCE_RADIANS
#include <Demos\FragCoordDemo.h>
#include <Demos\ShaderColorDemo.h>
#include <Demos\BufferDemo.h>
#include <Demos\VertexBufferDemo.h>
#include <Demos\LoadingObjDemo.h>
#include <Demos\DiffuseDemo.h>
#include <Demos\ADSDemo.h>
#include <Demos\DiscardDemo.h>
#include <memory>
using std::unique_ptr;

int main()
{
	auto window = unique_ptr<WindowInterface>(new DiscardDemo());
	return window->Execute();
}