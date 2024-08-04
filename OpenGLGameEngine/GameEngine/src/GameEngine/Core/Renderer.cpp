#include "Renderer.h"

namespace GameEngine {
	Renderer::Renderer()
	{
	}

	Renderer::Renderer(Shader* shader)
	{
		m_Shader = shader;
		m_UniformModel = m_Shader->GetModelLocation();
		m_UniformProjection = m_Shader->GetProjectionLocation();
	}

	void Renderer::RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, RenderableData* renderData)
	{

	}

	Renderer::~Renderer()
	{
		delete m_Shader;
	}
}
