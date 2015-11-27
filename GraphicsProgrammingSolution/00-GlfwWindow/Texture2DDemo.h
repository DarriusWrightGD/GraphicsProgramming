#pragma once
#include <Window\GlfwWindow.h>
#include <SOIL.h>
class Texture2DDemo : public GlfwWindow
{
public:
	Texture2DDemo();
	~Texture2DDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;
};

