#pragma once

#include <GL\gl_core_4_5.h>
#include <vector>
#include <functional>
#include <Rendering\GLSampler.h>
#include <Rendering\SamplerType.h>
#include <Rendering\TextureInfo.h>
#include <Rendering\Uniforms.h>

class GLRenderer;
class GuiRenderable
{
public:
	GuiRenderable(GLProgram & program, std::vector<UniformUpdate> uniforms = {});
	TextureInfo SetTexture(const char * filePath, SamplerType = SamplerType::Linear);
	void SetTexture(TextureInfo texture);
	void Update();
	bool visible = true;
private:
	TextureInfo guiTexture;
	GLProgram & program;
	GLRenderer * renderer;
	std::vector<UniformUpdate> instanceUniforms;
};