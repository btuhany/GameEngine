#pragma once
#include "Shader.h"
#include <GL/glew.h>
#include "RenderableData.h"


namespace GameEngine {
	class ENGINE_API Renderer
	{
	public:
		Renderer();
		Renderer(Shader* shader);
		virtual void RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, RenderableData* renderData);
		~Renderer();
	protected:
		Shader* m_Shader;
		GLuint m_UniformModel;
		GLuint m_UniformProjection;
	private:
		static std::vector<Renderer*> m_RendererList;
	};
}
