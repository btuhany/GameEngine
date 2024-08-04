#pragma once
#include "Camera.h"
#include "Window.h"
#include "Skybox.h"
#include "DirectionalLight.h"
#include <vector>
#include "Renderable3DObject.h"
#include "Input.h"
namespace GameEngine {
	class ENGINE_API Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual void Initialize();
		virtual void Start();
		virtual void Update(GLfloat deltaTime);
		void AddObject(Renderable3DObject* object);
		void AddShadowMapRenderableObject(IShadowMapRenderable* object);
		Camera* GetCamera();
		Skybox* GetSkybox();
		glm::vec3 GetBackgroundColor();
		bool UseSkyboxActive();
		void RenderScene(glm::mat4 projection);
		void SetPointLights();
		void SetSpotLights();
		void RenderSceneShadowMap();
		void RenderSceneOmniShadowMap();
		void SetDirectionalLight(DirectionalLight* dLight);
		DirectionalLight* GetDirectionalLight();
		int GetPointLightCount();
		int GetSpotLightCount();
		bool IsOmniShadowShaderSet();
	protected:
		void setBackgroundColor(glm::vec3 colour);
		void setCamera(Camera* camera);
		void setSkybox(Skybox* skybox);
		void useSkybox(bool useSkybox);
		void setOmniShadowShader(Shader* omniShadowShader);
		void addPointLight(const PointLight* pLight);
		void addSpotLight(const SpotLight* sLight);
		Camera* m_MainCamera;
	private:
		std::vector<Renderable3DObject*> m_RenderableObjectList;
		std::vector<IShadowMapRenderable*> m_ShadowMapRenderableList;
		Shader* m_OmniShadowShader;
		void updateObjects();
		void startObjects();
		PointLight m_PointLightList[MAX_POINT_LIGHTS];
		int m_PointLightCount = 0;
		SpotLight m_SpotLightList[MAX_SPOT_LIGHTS];
		int m_SpotLightCount = 0;
		glm::vec3 m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
		Skybox* m_Skybox;
		bool m_UseSkybox = false;
		DirectionalLight* m_DirectionalLight;
	};


}
