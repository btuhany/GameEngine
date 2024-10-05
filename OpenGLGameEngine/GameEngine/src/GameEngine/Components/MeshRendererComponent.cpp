#include "MeshRendererComponent.h"


namespace GameEngine
{
	void MeshRendererComponent::Render(GLuint modelLocation)
	{
		DrawMesh(modelLocation);
	}

	Shader* MeshRendererComponent::GetRenderDataShader()
	{
		return meshRenderData->shader;
	}

	void MeshRendererComponent::DrawMesh(GLuint uniformModel)
	{
		if (ownerEntity.expired())
		{
			LOG_CORE_WARN("MeshRendererComponent::DrawMesh owner entity is exprired!");
			return;
		}
		auto ownerEntityPtr = ownerEntity.lock();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntityPtr->transform->GetModelMatrix()));
		meshRenderData->materialData->UseMaterial(meshRenderData->shader->GetMatSpecularIntensityLocation(), meshRenderData->shader->GetMatShininessLocation());
		if (meshRenderData->textureData != NULL)
		{
			meshRenderData->textureData->UseTexture();
		}

		auto meshData = meshRenderData->meshData;
		glBindVertexArray(meshData->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->GetIBO());
		glDrawElements(GL_TRIANGLES, meshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}
