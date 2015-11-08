#include <Demos\FragCoordDemo.h>
#include <Demos\ShaderColorDemo.h>
#include <memory>
using std::unique_ptr;
int main()
{
	auto window = unique_ptr<WindowInterface>(new ShaderColorDemo());
	return window->Execute();
}