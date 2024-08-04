#pragma once
#include "Core.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "RenderableData.h"
#include "Log.h"
#include "Renderer.h"

namespace GameEngine {
	class ENGINE_API MeshRenderer : public Renderer
	{
	public:
		MeshRenderer();
		MeshRenderer(Shader* shader, Shader* dirShadowShader, Shader* omniShadowShader);
		MeshRenderer(Shader* shader, Shader* omniShadowShader);
		MeshRenderer(Shader* shader);
		//TODO: initialize func can be moved to constructors
		void Initialize(Camera* camera, DirectionalLight* light);
		void DrawData(GLuint uniformModel, glm::mat4 modelMatrix, RenderableData* renderData);
		void RenderObjectWithShader(glm::mat4 modelMatrix, glm::mat4 projectionMatrix, RenderableData* renderData) override;
		void RenderObjectForDirectionalShadow(glm::mat4 modelMatrix, DirectionalLight* directionalLight, RenderableData* renderData);
		void RenderObjectForOmniShadow(glm::mat4 modelMatrix, PointLight* pointLight, RenderableData* renderData);
		Shader* GetRenderShader();
		static void ClearRenderers();
		~MeshRenderer();
	private:
		static std::vector<MeshRenderer*> m_RendererList;
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
		Camera* m_Camera;
		DirectionalLight* m_DirLight;
	};
}
