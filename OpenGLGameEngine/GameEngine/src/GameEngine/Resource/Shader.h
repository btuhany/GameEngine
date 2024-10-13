#pragma once
#include "../Core.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "../Scene/DirectionalLight.h"
#include "../Scene/PointLight.h"
#include "../Scene/SpotLight.h"
#include "../ConstantValues.h"
namespace GameEngine {
	class ENGINE_API Shader
	{
	public:
		Shader();

		void CreateFromString(const char* vertexCode, const char* fragmentCode);
		void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
		void CreateFromFiles2D(const char* vertexLocation, const char* fragmentLocation);
		void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);
		void Validate();

		GLuint GetProjectionLocation();
		GLuint GetModelLocation();
		GLuint GetViewLocation();
		GLuint GetAmbientIntensityLocation();
		GLuint GetAmbientColourLocation();
		GLuint GetDiffuseIntensityLocation();
		GLuint GetDiffuseDirectionLocation();
		GLuint GetMatSpecularIntensityLocation();
		GLuint GetMatShininessLocation();
		GLuint GetCameraPositionLocation();
		GLuint GetOmniLightPosLocation();
		GLuint GetFarPlaneLocation();


		void SetDirectionalLight(std::shared_ptr<DirectionalLight> dLight);
		void SetPointLights(PointLight* pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
		void SetSpotLights(SpotLight* sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
		void SetTextureUnit(GLuint textureUnit);
		void SetDirectionalShadowMap(GLuint textureUnit);
		void SetDirectionalLightTransform(glm::mat4* lightTransform);
		void SetLightMatrices(std::vector<glm::mat4> lightMatrices);
		void SetUseDirLightShadow(bool active);

		void UseShader();
		void ClearShader();

		~Shader();

	private:
		int pointLightCount;
		int spotLightCount;

		GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformCameraPosition;
		GLuint uniformMatSpecularIntensity, uniformMatShininess;
		GLuint uniformTexture, uniformDirectionalLightTransform, uniformDirectionalShadowMap;
		GLuint uniformOmniLightPos, uniformFarPlane;

		GLuint uniformLightMatrices[6];

		struct {
			GLuint UniformColour;
			GLuint UniformAmbientIntensity;
			GLuint UniformDiffuseIntensity;
			GLuint UniformDirection;
		} m_UniformDirectionalLight;

		GLuint m_UniformPointLightCount;

		struct {
			GLuint UniformColour;
			GLuint UniformAmbientIntensity;
			GLuint UniformDiffuseIntensity;

			GLuint UniformPosition;
			GLuint UniformConstant;
			GLuint UniformLinear;
			GLuint UniformExponent;
			GLuint UniformUseOmniShadow;

		} m_UniformPointLights[MAX_POINT_LIGHTS];

		GLuint m_UniformSpotLightCount;
		struct {
			GLuint UniformColour;
			GLuint UniformAmbientIntensity;
			GLuint UniformDiffuseIntensity;

			GLuint UniformPosition;
			GLuint UniformConstant;
			GLuint UniformLinear;
			GLuint UniformExponent;
			GLuint UniformUseOmniShadow;

			GLuint UniformDirection;
			GLuint UniformEdge;
		} m_UniformSpotLights[MAX_SPOT_LIGHTS];

		struct {
			GLuint ShadowMap;
			GLuint FarPlane;
		} m_UniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

		std::string ReadFile(const char* fileLocation);
		void CompileShader(const char* vertexCode, const char* fragmentCode);
		void CompileShader2D(const char* vertexCode, const char* fragmentCode);
		void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
		void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);


		void CompileProgram();
		void CompileProgram2D();
	};
}
