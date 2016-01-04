#include <GL\gl_core_4_5.h>
#include <vector>
#include <functional>
#include <Rendering\GLSampler.h>
#include <Rendering\SamplerType.h>
#include <Rendering\TextureInfo.h>
#include <Rendering\Uniforms.h>

class GLRenderer;
class FullScreenRenderable
{
public:
	FullScreenRenderable(GLProgram & program, std::vector<UniformUpdate> uniforms = {});
	void SetTexture(TextureInfo texture);
	void Update();
private:
	TextureInfo fullScreenTexture;
	GLProgram & program;
	GLRenderer * renderer;
	std::vector<UniformUpdate> instanceUniforms;
};