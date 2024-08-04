#pragma once
#include "Core.h"
#include "MeshRenderer.h"
namespace GameEngine {
	class ENGINE_API RenderableObject
	{
	public:
		RenderableObject();
		~RenderableObject();
		RenderableObject(MeshRenderer* renderer, RenderableData* renderableData);
		void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, Camera* mainCamera, DirectionalLight* dirLight);
		void RenderShadowMap(DirectionalLight* dirLight);
		void RenderOmniShadowMap(PointLight* pointLight);
		void TranslateTransform(glm::vec3 translateVector);
		void RotateTransform(float angle, glm::vec3 rotateVector);
		void ScaleTransform(glm::vec3 scaleVector);
		Shader* GetRenderShader();
		void ClearRenderableObject();
	private:
		MeshRenderer* m_Renderer;
		RenderableData* m_RenderableData;
		glm::mat4 m_TransformModelMatrix;
	};
}
