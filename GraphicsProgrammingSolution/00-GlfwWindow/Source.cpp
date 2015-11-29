#define GLM_FORCE_RADIANS
#include<Demos\Light\DirectionalLightDemo.h>
#include<Demos\Light\ADSHalfwayVecDemo.h>
#include <Demos\Light\SpotLightDemo.h>
#include <memory>
using std::unique_ptr;

int main()
{
	auto window = unique_ptr<WindowInterface>(new SpotLightDemo());
	return window->Execute();
}