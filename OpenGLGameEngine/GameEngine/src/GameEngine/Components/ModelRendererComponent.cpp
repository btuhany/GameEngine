#include "ModelRendererComponent.h"

namespace GameEngine
{
	void ModelRendererComponent::Render(GLuint modelLocation)
	{
		DrawModel(modelLocation);
	}

	void ModelRendererComponent::setModelRenderData(std::shared_ptr<ModelRenderData> modelRenderData)
	{
		m_ModelRenderData = modelRenderData;
	}

	std::shared_ptr<Shader> ModelRendererComponent::getRenderDataShader()
	{
		return m_ModelRenderData->shader;
	}

	void ModelRendererComponent::DrawModel(GLuint uniformModel)
	{
		//TODOby
		if (m_OwnerEntity.expired())
		{
			LOG_CORE_WARN("ModelRendererComponent::DrawModel owner entity is exprired!");
			return;
		}
		auto ownerEntityPtr = m_OwnerEntity.lock();

		m_ModelRenderData->material->UseMaterial(m_ModelRenderData->shader->GetMatSpecularIntensityLocation(), m_ModelRenderData->shader->GetMatShininessLocation());

		if (m_ModelRenderData->texture != NULL)
		{
			m_ModelRenderData->texture->UseTexture();
		}

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntityPtr->transform->GetModelMatrix()));
		for (size_t i = 0; i < m_ModelRenderData->model->m_MeshList.size(); i++)
		{
			unsigned int materialIndex = m_ModelRenderData->model->m_MeshToTex[i];

			if (materialIndex < m_ModelRenderData->model->m_TextureList.size() && m_ModelRenderData->model->m_TextureList[materialIndex])
			{
				m_ModelRenderData->model->m_TextureList[materialIndex]->UseTexture();
			}

			glBindVertexArray(m_ModelRenderData->model->m_MeshList[i]->GetVAO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ModelRenderData->model->m_MeshList[i]->GetIBO());
			glDrawElements(GL_TRIANGLES, m_ModelRenderData->model->m_MeshList[i]->GetIndexCount(), GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}


}
