#pragma once
#include "Core.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "RenderableData.h"
namespace GameEngine {
	class ENGINE_API Renderer
	{
	public:
		Renderer();
		Renderer(Shader* shader, Shader* dirShadowShader, Shader* omniShadowShader);
		void DrawData(GLuint uniformModel, glm::mat4 modelMatrix, RenderableData* renderData);
		void RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, RenderableData* renderData, DirectionalLight* directionalLight);
		void RenderObjectForDirectionalShadow(glm::mat4 modelMatrix, DirectionalLight* directionalLight, RenderableData* renderData);
		void RenderObjectForOmniShadow(glm::mat4 modelMatrix, PointLight* pointLight, RenderableData* renderData);
		Shader* GetRenderShader();
		static void ClearRenderers();
		~Renderer();
	private:
		static std::vector<Renderer*> m_RendererList;
		Shader* m_Shader;
		Shader* m_DirShadowShader;
		Shader* m_OmniShadowShader;
		GLuint m_UniformModel;
		GLuint m_UniformProjection;
		GLuint m_UniformView;
		GLuint m_UniformMatSpecularInstensity;
		GLuint m_UniformMatShininess;
		GLuint m_UniformCameraPosition;
		glm::mat4 m_LightTransform;
	};
}