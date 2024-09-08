#include "MeshRendererComponent.h"


namespace GameEngine
{
	void MeshRendererComponent::Render(glm::mat4 projectionMatrix)
	{
		auto shader = meshRenderData->shader;

		shader->UseShader();

		glUniform3f(shader->GetCameraPositionLocation(), camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);
		glUniformMatrix4fv(shader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(shader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera->CalculateViewMatrix()));

		shader->SetTextureUnit(2);
		BindDirLightConfigToShader();

		shader->Validate();

		DrawMesh(shader->GetModelLocation());
	}

	void MeshRendererComponent::RenderToDirLightShadowMap()
	{
		if (dirShadowShader == nullptr)
		{
			LOG_CORE_ERROR("Directional shadow shader is null!");
			return;
		}
		dirShadowShader->UseShader();

		glm::mat4 lightTransform = directionalLight->CalculateLightTransform();
		dirShadowShader->SetDirectionalLightTransform(&lightTransform);
		dirShadowShader->Validate();

		DrawMesh(dirShadowShader->GetModelLocation());
	}

	void MeshRendererComponent::RenderToPointLightShadowMap(PointLight* pointLight)
	{
		//m_OmniShadowShader->UseShader();
		glUniform3f(omniShadowShader->GetOmniLightPosLocation(), pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
		glUniform1f(omniShadowShader->GetFarPlaneLocation(), pointLight->GetFarPlane());
		omniShadowShader->SetLightMatrices(pointLight->CalculateLightTransform());

		DrawMesh(omniShadowShader->GetModelLocation());
	}

	void MeshRendererComponent::BindDirLightConfigToShader()
	{
		auto shader = meshRenderData->shader;
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

	void MeshRendererComponent::DrawMesh(GLuint uniformModel)
	{
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntity->GetComponent<Transform>()->GetModelMatrix()));
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
