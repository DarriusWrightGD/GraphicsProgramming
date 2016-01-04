#include "FullScreenRenderable.h"
#include <Util\ServiceLocator.h>
#include <Rendering\GLRenderer.h>

FullScreenRenderable::FullScreenRenderable(GLProgram & program, std::vector<UniformUpdate> uniforms) : program(program)
{
	renderer = Services.Get<GLRenderer>();
	instanceUniforms.resize(uniforms.size());
	std::move(uniforms.begin(), uniforms.end(), instanceUniforms.begin());
}

void FullScreenRenderable::SetTexture(TextureInfo texture)
{
	fullScreenTexture = texture;
}

void FullScreenRenderable::Update()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(fullScreenTexture.type, fullScreenTexture.id);
	glBindSampler(0, fullScreenTexture.sampler);

	program.Update();
	for (auto uniform : instanceUniforms)
	{
		program.UpdateUniform(uniform.name, { uniform.type, uniform.value });
	}
}
