#include "MeshRendererComponent.h"


namespace GameEngine
{
	void MeshRendererComponent::Render(GLuint modelLocation)
	{
		drawMesh(modelLocation);
	}

	void MeshRendererComponent::setMeshRenderData(std::shared_ptr<MeshRenderData> meshRenderData)
	{
		m_MeshRenderData = meshRenderData;
	}

	std::shared_ptr<Shader> MeshRendererComponent::getRenderDataShader()
	{
		return m_MeshRenderData->shader;
	}

	void MeshRendererComponent::drawMesh(GLuint uniformModel)
	{
		if (m_OwnerEntity.expired())
		{
			LOG_CORE_WARN("MeshRendererComponent::DrawMesh owner entity is exprired!");
			return;
		}
		auto ownerEntityPtr = m_OwnerEntity.lock();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntityPtr->transform->GetModelMatrix()));
		m_MeshRenderData->material->UseMaterial(m_MeshRenderData->shader->GetMatSpecularIntensityLocation(), m_MeshRenderData->shader->GetMatShininessLocation());
		if (m_MeshRenderData->texture != NULL)
		{
			m_MeshRenderData->texture->UseTexture();
		}

		auto meshData = m_MeshRenderData->mesh;
		glBindVertexArray(meshData->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->GetIBO());
		glDrawElements(GL_TRIANGLES, meshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}
