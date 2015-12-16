#define GLM_FORCE_RADIANS

#include <Demos.h>
#include <memory>
using std::unique_ptr;

int main()
{
	auto window = unique_ptr<WindowInterface>(new EdgeDetection());
	return window->Execute();
}