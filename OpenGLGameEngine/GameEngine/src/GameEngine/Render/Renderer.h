#pragma once
#include <memory.h>
#include "../Scene/Scene.h"
#include "../Scene/Skybox.h"
#include "../Scene/Camera.h"
#include "../Core.h"
#include "../Scene/DirectionalLight.h"
#include "../Entities/MeshEntity.h"
#include "../Entities/ModelEntity.h"
#include "../Event/EventManager.h"
#include "../Event/ComponentEvent.h"
#include "stdio.h"
namespace GameEngine
{
	class ENGINE_API Renderer
	{
	public:
		//TODO initialize from scene
		Renderer();
		~Renderer();
		//Renderer(std::shared_ptr<Skybox> skybox, glm::vec3 backgroundColor, std::shared_ptr<Camera> camera);
		void Initialize(Scene* scene);
	public:
		void renderPass(glm::mat4 projectionMatrix, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount);
		void directionalShadowMapPass(DirectionalLight* dLight);
		void omniShadowMapPass(Shader* omniShadowShader, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount);
	private:
		//std::vector<std::shared_ptr<MeshRendererComponent>> m_meshRendererComponents;
		//std::vector<std::shared_ptr<ModelRendererComponent>> m_modelRendererComponents;
		//void OnComponentAssigned(std::shared_ptr<ComponentAssignedEvent> componentAssignEvent);
		std::vector<std::shared_ptr<RendererComponent>> m_RendererComponents;
		glm::vec3 m_BackgroundColor;
		std::shared_ptr<Skybox> m_Skybox;
		std::shared_ptr<Camera> m_Camera;
		Shader* m_DirLightShadowShader;
		Shader* m_OmniShadowShader;
		DirectionalLight* m_DirLight;
		bool m_IsInitialized = false;
		void onComponentAssigned(std::shared_ptr<ComponentEvent> componentEvent);
		bool isAbleToRender(std::shared_ptr<RendererComponent> rendererComponent);
	};
}

