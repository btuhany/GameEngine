#pragma once
#include "Camera.h"
#include "Window.h"
#include "Skybox.h"
#include "DirectionalLight.h"
#include <vector>
#include "RenderableObject.h"
namespace GameEngine {
	class ENGINE_API Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual void Initialize();
		virtual void Start();
		virtual void Update(GLfloat deltaTime);
		void AddObject(RenderableObject* object);
		Camera* GetCamera();
		Skybox* GetSkybox();
		glm::vec3 GetBackgroundColor();
		bool UseSkyboxActive();
		void RenderScene(glm::mat4 projection);
		void SetPointLights();
		void SetSpotLights();
		void RenderSceneShadowMap();
		void RenderSceneOmniShadowMap();
		void setDirectionalLight(DirectionalLight* dLight);
		DirectionalLight* getDirectionalLight();
		int GetPointLightCount();
		int GetSpotLightCount();
	protected:
		void setBackgroundColor(glm::vec3 colour);
		void setCamera(Camera* camera);
		void setSkybox(Skybox* skybox);
		void useSkybox(bool useSkybox);
		void setOmniShadowShader(Shader* omniShadowShader);
		void AddPointLight(const PointLight* pLight);
		void AddSpotLight(const SpotLight* sLight);
	private:
		std::vector<RenderableObject*> m_RenderableObjectList;
		Shader* m_OmniShadowShader;
		void updateObjects();
		void startObjects();
		PointLight m_PointLightList[MAX_POINT_LIGHTS];
		int m_PointLightCount = 0;
		SpotLight m_SpotLightList[MAX_SPOT_LIGHTS];
		int m_SpotLightCount = 0;
		glm::vec3 m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
		Camera* m_MainCamera;
		Skybox* m_Skybox;
		bool m_UseSkybox = false;
		DirectionalLight* m_DirectionalLight;
	};


}
