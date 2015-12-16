#pragma once
#include <vector>
#include <Rendering\VertexLayout.h>
#include <Rendering\SamplerType.h>
#include <Rendering\GLSampler.h>
#include <Rendering\Uniforms.h>
#include <Rendering\Renderpass.h>
#include <unordered_map>
#include <vec2.hpp>

class Renderable;
class GLRenderer 
{
public:
	static constexpr int NUM_RENDERABLES = 100;
	GLRenderer() noexcept;
	~GLRenderer() noexcept;
	void Render();
	void Render(Renderable * renderable);
	Renderable * AddRenderable(GLProgram & program,const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layout, const std::vector<UniformUpdate> & instanceUniforms);
	RenderPass * AddRenderPass(glm::vec2 size, SamplerType samplerType, int numberOfColorAttachments = 1);
	GLSampler GetSampler(SamplerType type);
private:
	std::vector<Renderable> renderables;
	std::vector<RenderPass*> renderPasses;
	std::unordered_map<SamplerType, GLSampler> samplerMap;
	void InitializeSamplers();
	bool samplersInitialized;
};


