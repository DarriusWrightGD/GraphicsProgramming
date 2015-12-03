#define GLM_FORCE_RADIANS
#include<Demos\Light\DirectionalLightDemo.h>
#include<Demos\Light\ADSHalfwayVecDemo.h>
#include <Demos\Light\SpotLightDemo.h>
#include <Demos\Light\CartoonShadingDemo.h>
#include <Demos\Misc\FogDemo.h>
#include <Demos\Texture\Texture2DDemo.h>
#include <Demos\Texture\MultiTextureDemo.h>
#include <Demos\Texture\AlphaMapDemo.h>
#include <Demos\Texture\NormalMapDemo.h>
#include <memory>
using std::unique_ptr;

int main()
{
	auto window = unique_ptr<WindowInterface>(new NormalMapDemo());
	return window->Execute();
}