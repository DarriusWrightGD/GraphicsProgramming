#pragma once
#include <vector>
#include <Rendering\VertexLayout.h>
#include <Rendering\SamplerType.h>
#include <Rendering\GLSampler.h>
#include <Rendering\Uniforms.h>
#include <Rendering\Renderpass.h>
#include <Rendering\DrawFunction.h>
#include <unordered_map>
#include <vec2.hpp>

class Renderable;
class GuiRenderable;
class FullScreenRenderable;
class GLRenderer 
{
public:
	static constexpr int NUM_RENDERABLES = 100;
	GLRenderer() noexcept;
	~GLRenderer() noexcept;
	void Render();
	void RenderObjects();
	void RenderUi();
	void RenderFullScreen();
	void Render(Renderable * renderable);
	void SetFullScreenRenderable(FullScreenRenderable * renderable);
	Renderable * AddRenderable(GLProgram & program, const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layout, const std::vector<UniformUpdate> & instanceUniforms, GLint drawMode = GL_TRIANGLES, DrawFunction function = DrawFunction::ELEMENTS);
	GuiRenderable * AddGuiRenderable(GLProgram & program, const std::vector<UniformUpdate> & instanceUniforms);
	RenderPass * AddRenderPass(glm::vec2 size, SamplerType samplerType, int numberOfColorAttachments = 1);
	TextureInfo CreateTexture(GLuint textureIndex, const char * filePath,  SamplerType sampler = SamplerType::Linear);
	GLSampler GetSampler(SamplerType type);
private:
	std::vector<Renderable> renderables;
	std::vector<GuiRenderable> guiRenderables;
	std::vector<RenderPass*> renderPasses;
	std::unordered_map<SamplerType, GLSampler> samplerMap;
	void InitializeSamplers();
	bool samplersInitialized;
	FullScreenRenderable * fullScreenRenderable = nullptr;
};


