#include "ModelRendererComponent.h"

namespace GameEngine
{
	void ModelRendererComponent::Render(GLuint modelLocation)
	{
		//auto shader = modelRenderData->shader;

		//shader->UseShader();

		//glUniform3f(shader->GetCameraPositionLocation(), camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);
		//glUniformMatrix4fv(shader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		//glUniformMatrix4fv(shader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera->CalculateViewMatrix()));

		//shader->SetTextureUnit(2);
		//BindDirLightConfigToShader();

		//shader->Validate();



		DrawModel(modelLocation);
	}

	void ModelRendererComponent::RenderToDirLightShadowMap()
	{
		//if (dirShadowShader == nullptr)
		//{
		//	LOG_CORE_ERROR("Directional shadow shader is null!");
		//	return;
		//}
		//dirShadowShader->UseShader();

		//glm::mat4 lightTransform = directionalLight->CalculateLightTransform();
		//dirShadowShader->SetDirectionalLightTransform(&lightTransform);
		//dirShadowShader->Validate();

		//DrawModel(dirShadowShader->GetModelLocation());
	}

	void ModelRendererComponent::RenderToPointLightShadowMap(PointLight* pointLight)
	{
		////omniShadowShader->UseShader();
		//glUniform3f(omniShadowShader->GetOmniLightPosLocation(), pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
		//glUniform1f(omniShadowShader->GetFarPlaneLocation(), pointLight->GetFarPlane());
		//omniShadowShader->SetLightMatrices(pointLight->CalculateLightTransform());

		//DrawModel(omniShadowShader->GetModelLocation());
	}

	void ModelRendererComponent::DrawModel(GLuint uniformModel)
	{
		//TODOby
		modelRenderData->materialData->UseMaterial(modelRenderData->shader->GetMatSpecularIntensityLocation(), modelRenderData->shader->GetMatShininessLocation());

		if (modelRenderData->textureData != NULL)
		{
			modelRenderData->textureData->UseTexture();
		}

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntity->GetComponent<Transform>()->GetModelMatrix()));
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
	void ModelRendererComponent::BindDirLightConfigToShader()
	{
		auto shader = modelRenderData->shader;
		if (directionalLight != nullptr)
		{
			shader->SetDirectionalLight(directionalLight);
			//TODO: should be in if
			glm::mat4 lightTransform = directionalLight->CalculateLightTransform();
			shader->SetDirectionalLightTransform(&lightTransform);
			if (directionalLight->GetShadowMap() != nullptr)
			{
				directionalLight->GetShadowMap()->Read(GL_TEXTURE3);
				shader->SetDirectionalShadowMap(3);
			}
		}
	}
	Shader* ModelRendererComponent::GetRenderDataShader()
	{
		return modelRenderData->shader;
	}
}
