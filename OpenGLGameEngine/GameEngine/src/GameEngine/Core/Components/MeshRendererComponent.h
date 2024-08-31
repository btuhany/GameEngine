#pragma once
#include <memory.h>
#include "RendererComponent.h"
#include "../MeshRenderData.h"
#include "../Camera.h"
#include "Transform.h"
#include "../Entity.h"

namespace GameEngine
{
	class ENGINE_API MeshRendererComponent : public RendererComponent 
	{
	public:
		void Render(glm::mat4 projectionMatrix) override;
		std::shared_ptr<MeshRenderData> meshRenderData;

		//TODOby fix
		Camera* camera;
		DirectionalLight* directionalLight;
	private:
		void DrawMesh();
		void HandleDirectionalLight();
	};
}
