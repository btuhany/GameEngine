#pragma once
#include <memory>
#include "Camera.h"
#include "../Engine/Window.h"
#include "Skybox.h"
#include "DirectionalLight.h"
#include <vector>
#include "../Engine/Input.h"
#include "../Entities/RenderableEntity.h"
#include "../Entities/MeshEntity.h"
#include "../Entities/ModelEntity.h"
namespace GameEngine {
	class ENGINE_API Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual void Initialize();
		virtual void Start();
		virtual void Update(GLfloat deltaTime);

		std::shared_ptr<Camera> GetCamera();
		std::shared_ptr<Skybox> GetSkybox();
		glm::vec3 GetBackgroundColor();
		bool UseSkyboxActive();
		void SetDirectionalLight(DirectionalLight* dLight);
		DirectionalLight* GetDirectionalLight();
		int GetPointLightCount();
		int GetSpotLightCount();
		bool IsOmniShadowShaderSet();
		Shader* m_OmniShadowShader;
		PointLight m_PointLightList[MAX_POINT_LIGHTS];
		int m_PointLightCount = 0;
		SpotLight m_SpotLightList[MAX_SPOT_LIGHTS];
		int m_SpotLightCount = 0;
	protected:
		void setBackgroundColor(glm::vec3 colour);
		void setCamera(std::shared_ptr<Camera> camera);
		void setSkybox(std::shared_ptr<Skybox> skybox);
		void useSkybox(bool useSkybox);
		void setOmniShadowShader(Shader* omniShadowShader);
		void addPointLight(const PointLight* pLight);
		void addSpotLight(const SpotLight* sLight);
		std::shared_ptr<Camera> m_MainCamera;
	private:
		void updateObjects();
		void startObjects();
		glm::vec3 m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
		std::shared_ptr <Skybox> m_Skybox;
		bool m_UseSkybox = false;
		DirectionalLight* m_DirectionalLight;
	public:
		std::vector<std::shared_ptr<MeshEntity>> RenderableMeshEntitiesPublic;
		std::vector<std::shared_ptr<ModelEntity>> RenderableModelEntitiesPublic;
	};


}
