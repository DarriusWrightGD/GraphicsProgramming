#define GLM_FORCE_RADIANS
#include<Demos\Light\DirectionalLightDemo.h>
#include<Demos\Light\ADSHalfwayVecDemo.h>
#include <memory>
using std::unique_ptr;

int main()
{
	auto window = unique_ptr<WindowInterface>(new ADSHalfwayVecDemo());
	return window->Execute();
}