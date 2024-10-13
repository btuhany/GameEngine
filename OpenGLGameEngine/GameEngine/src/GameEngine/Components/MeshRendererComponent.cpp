#include "MeshRendererComponent.h"


namespace GameEngine
{
	void MeshRendererComponent::Render(GLuint modelLocation)
	{
		DrawMesh(modelLocation);
	}

	std::shared_ptr<Shader> MeshRendererComponent::GetRenderDataShader()
	{
		return meshRenderData->shader;
	}

	void MeshRendererComponent::DrawMesh(GLuint uniformModel)
	{
		if (m_ownerEntity.expired())
		{
			LOG_CORE_WARN("MeshRendererComponent::DrawMesh owner entity is exprired!");
			return;
		}
		auto ownerEntityPtr = m_ownerEntity.lock();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntityPtr->transform->GetModelMatrix()));
		meshRenderData->material->UseMaterial(meshRenderData->shader->GetMatSpecularIntensityLocation(), meshRenderData->shader->GetMatShininessLocation());
		if (meshRenderData->texture != NULL)
		{
			meshRenderData->texture->UseTexture();
		}

		auto meshData = meshRenderData->mesh;
		glBindVertexArray(meshData->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->GetIBO());
		glDrawElements(GL_TRIANGLES, meshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}
