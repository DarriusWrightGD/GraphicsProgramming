#include "GuiRenderable.h"
#include <Util\ServiceLocator.h>
#include <Rendering\GLRenderer.h>

GuiRenderable::GuiRenderable(GLProgram & program, std::vector<UniformUpdate> uniforms) : program(program)
{
	renderer = Services.Get<GLRenderer>();
	instanceUniforms.resize(uniforms.size());
	std::move(uniforms.begin(), uniforms.end(), instanceUniforms.begin());
}

TextureInfo GuiRenderable::SetTexture(const char * filePath, SamplerType type)
{
	guiTexture = renderer->CreateTexture(0, filePath, type);
	return guiTexture;
}

void GuiRenderable::SetTexture(TextureInfo texture)
{
	guiTexture = texture;
}

void GuiRenderable::Update()
{
	glActiveTexture(GL_TEXTURE0 );
	glBindTexture(guiTexture.type, guiTexture.id);
	glBindSampler(0, guiTexture.sampler);

	program.Update();
	for (auto uniform : instanceUniforms)
	{
		program.UpdateUniform(uniform.name, { uniform.type, uniform.value });
	}
}
