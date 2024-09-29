#include "ModelRendererComponent.h"

namespace GameEngine
{
	void ModelRendererComponent::Render(GLuint modelLocation)
	{
		DrawModel(modelLocation);
	}

	Shader* ModelRendererComponent::GetRenderDataShader()
	{
		return modelRenderData->shader;
	}

	void ModelRendererComponent::DrawModel(GLuint uniformModel)
	{
		//TODOby
		modelRenderData->materialData->UseMaterial(modelRenderData->shader->GetMatSpecularIntensityLocation(), modelRenderData->shader->GetMatShininessLocation());

		if (modelRenderData->textureData != NULL)
		{
			modelRenderData->textureData->UseTexture();
		}

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntity->transform->GetModelMatrix()));
		for (size_t i = 0; i < modelRenderData->modelData->m_MeshList.size(); i++)
		{
			unsigned int materialIndex = modelRenderData->modelData->m_MeshToTex[i];

			if (materialIndex < modelRenderData->modelData->m_TextureList.size() && modelRenderData->modelData->m_TextureList[materialIndex])
			{
				modelRenderData->modelData->m_TextureList[materialIndex]->UseTexture();
			}

			glBindVertexArray(modelRenderData->modelData->m_MeshList[i]->GetVAO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelRenderData->modelData->m_MeshList[i]->GetIBO());
			glDrawElements(GL_TRIANGLES, modelRenderData->modelData->m_MeshList[i]->GetIndexCount(), GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}


}
