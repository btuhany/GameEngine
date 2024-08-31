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
		HandleDirectionalLight();

		shader->Validate();

		glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(ownerEntity->GetComponent<Transform>()->GetModelMatrix()));

		meshRenderData->materialData->UseMaterial(shader->GetMatSpecularIntensityLocation(), shader->GetMatShininessLocation());

		if (meshRenderData->textureData != NULL)
		{
			meshRenderData->textureData->UseTexture();
		}
		DrawMesh();
	}

	void MeshRendererComponent::HandleDirectionalLight()
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

	void MeshRendererComponent::DrawMesh()
	{
		auto meshData = meshRenderData->meshData;
		glBindVertexArray(meshData->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->GetIBO());
		glDrawElements(GL_TRIANGLES, meshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}
