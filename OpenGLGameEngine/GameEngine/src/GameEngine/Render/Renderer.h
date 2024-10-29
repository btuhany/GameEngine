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
#include "../Event/SceneCameraChangedEvent.h"
#include "../Debugging/Log.h"
#include "../Render/MeshRenderData.h"
#include "../Components/Transform.h"
#include "stdio.h"
#include <unordered_map>
#include "../Render/DebugRenderData.h"
#include "../StartModeSettings.h"
namespace GameEngine
{
	class ENGINE_API Renderer
	{
	public:
		Renderer();
		~Renderer();
		void Initialize(Scene* scene, GLfloat bufferRatio);

		void Draw(bool shadowPassActive, bool renderDirLightShadow, bool renderOmniLightShadow);
		void DebugPass(glm::mat4 projectionMatrix);
		void RenderPass(glm::mat4 projectionMatrix, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount);
		void DirectionalShadowMapPass(std::shared_ptr<DirectionalLight> dLight);
		void OmniShadowMapPass(std::shared_ptr<Shader> omniShadowShader, PointLight* pLightList, unsigned int plightCount, SpotLight* sLightList, unsigned int slightCount);

	private:
		std::vector<std::shared_ptr<RendererComponent>> m_RendererComponents;
		glm::vec3 m_BackgroundColor;
		std::shared_ptr<Skybox> m_Skybox;
		std::shared_ptr<Camera> m_Camera;
		std::shared_ptr<Shader> m_DirLightShadowShader;
		std::shared_ptr<Shader> m_OmniShadowShader;
		std::shared_ptr<DirectionalLight> m_DirLight;
		Scene* m_Scene;
		bool m_IsInitialized = false;
		void onComponentEvent(std::shared_ptr<ComponentEvent> componentEvent);
		void onSceneCameraChangedEvent(std::shared_ptr<SceneCameraChangedEvent> sceneCameraChangedEventData);
		bool isAbleToRender(std::shared_ptr<RendererComponent> rendererComponent);
		GLfloat m_BufferRatio;

#if _DEBUG
	public:
		static std::unordered_map<std::shared_ptr<DebugRenderData>, std::weak_ptr<Transform>> DebugMeshRenderDataTransformMap;
#endif
	};
}

