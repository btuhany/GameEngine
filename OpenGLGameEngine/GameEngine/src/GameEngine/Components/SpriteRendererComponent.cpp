#include "SpriteRendererComponent.h"

namespace GameEngine
{
	void SpriteRendererComponent::Render(GLuint modelLocation)
	{
		drawSprite(modelLocation);
	}

	std::shared_ptr<Shader> SpriteRendererComponent::getRenderDataShader()
	{
		return m_SpriteRenderData->shader;
	}

	void SpriteRendererComponent::ChangeRenderShader(std::shared_ptr<Shader> newRenderShader)
	{
		auto newSpriteRenderData = std::make_shared<SpriteRenderData>(m_SpriteRenderData->texture, m_SpriteRenderData->material, newRenderShader);
		m_SpriteRenderData = newSpriteRenderData;
	}

	bool SpriteRendererComponent::IsShadowRenderable()
	{
		return false;
	}
	void SpriteRendererComponent::setSpriteRenderData(std::shared_ptr<SpriteRenderData> spriteRenderData)
	{
		m_SpriteRenderData = spriteRenderData;
	}
	void SpriteRendererComponent::drawSprite(GLuint uniformModel)
	{
		if (m_OwnerEntity.expired())
		{
			LOG_CORE_WARN("SpriteRendererComponent::DrawMesh owner entity is exprired!");
			return;
		}
		auto ownerEntityPtr = m_OwnerEntity.lock();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(ownerEntityPtr->transform->GetModelMatrix()));
		m_SpriteRenderData->material->UseMaterial(m_SpriteRenderData->shader->GetMatSpecularIntensityLocation(), m_SpriteRenderData->shader->GetMatShininessLocation());
		if (m_SpriteRenderData->texture != NULL)
		{
			m_SpriteRenderData->texture->UseTexture();
		}

		auto spriteMeshData = m_SpriteRenderData->quadMesh;
		glBindVertexArray(spriteMeshData->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteMeshData->GetIBO());
		glDrawElements(GL_TRIANGLES, spriteMeshData->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}
