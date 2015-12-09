#pragma once
#include <vector>
#include <Rendering\VertexLayout.h>
#include <Rendering\SamplerType.h>
#include <Rendering\GLSampler.h>
#include <Rendering\Uniforms.h>
#include <unordered_map>

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
	GLSampler GetSampler(SamplerType type);
private:
	std::vector<Renderable> renderables;
	std::unordered_map<SamplerType, GLSampler> samplerMap;
	void InitializeSamplers();
	bool samplersInitialized;
};


