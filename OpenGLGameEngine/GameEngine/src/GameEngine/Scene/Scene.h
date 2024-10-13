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
#include  <iostream>
#include <stdio.h>
namespace GameEngine {
	class ENGINE_API Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual void Initialize();
		virtual void Start();
		virtual void Update(GLfloat deltaTime);

		std::shared_ptr<Camera> getCamera();
		std::shared_ptr<Skybox> getSkybox();
		glm::vec3 getBackgroundColor();
		int getPointLightCount();
		int getSpotLightCount();
		std::shared_ptr<Shader> getOmniShadowShader();

		std::shared_ptr<Shader> getDirectionalLightShadowShader();
		void setDirectionalLightShadowShader(std::shared_ptr<Shader> dirShadowShader);

		void setDirectionalLight(DirectionalLight* dLight);
		DirectionalLight* getDirectionalLight();

		bool IsOmniShadowShaderSet();

		PointLight m_PointLightList[MAX_POINT_LIGHTS];
		int m_PointLightCount = 0;
		SpotLight m_SpotLightList[MAX_SPOT_LIGHTS];
		int m_SpotLightCount = 0;
		bool isInitialized = false;
	protected:
		void setBackgroundColor(glm::vec3 colour);
		void setCamera(std::shared_ptr<Camera> camera);
		void setSkybox(std::shared_ptr<Skybox> skybox);
		void setOmniShadowShader(std::shared_ptr<Shader> omniShadowShader);
		void addPointLight(const PointLight* pLight);
		void addSpotLight(const SpotLight* sLight);
		std::shared_ptr<Camera> m_MainCamera;
		void instantiateGameEntity(std::shared_ptr<GameEntity> entity, bool isActive = true);
		void destroyGameEntity(std::shared_ptr<GameEntity> entity, bool disableFirst);
	private:
		std::shared_ptr<Shader> m_DirLightShadowShader;
		std::shared_ptr<Shader> m_OmniShadowShader;
		DirectionalLight* m_DirectionalLight;
		std::vector<std::shared_ptr<GameEntity>> m_GameEntities;
		void updateObjects();
		void startObjects();
		glm::vec3 m_BackgroundColour = glm::vec3(0.0f, 0.0f, 0.0f);
		std::shared_ptr <Skybox> m_Skybox;
	};


}
