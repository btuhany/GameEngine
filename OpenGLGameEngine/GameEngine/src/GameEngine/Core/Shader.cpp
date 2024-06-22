#include "Shader.h"
namespace GameEngine {
	Shader::Shader()
	{
		shaderID = 0;
		uniformModel = 0;
		uniformProjection = 0;
		uniformView = 0;

		pointLightCount = 0;
		spotLightCount = 0;
	}

	void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
	{
		CompileShader(vertexCode, fragmentCode);
	}

	void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
	{
		std::string vertexString = ReadFile(vertexLocation);
		std::string fragmentString = ReadFile(fragmentLocation);
		const char* vertexCode = vertexString.c_str();
		const char* fragmentCode = fragmentString.c_str();

		CompileShader(vertexCode, fragmentCode);
	}

	void Shader::CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation)
	{
		std::string vertexString = ReadFile(vertexLocation);
		std::string geomString = ReadFile(geometryLocation);
		std::string fragmentString = ReadFile(fragmentLocation);
		const char* vertexCode = vertexString.c_str();
		const char* geometryCode = geomString.c_str();
		const char* fragmentCode = fragmentString.c_str();

		CompileShader(vertexCode, geometryCode, fragmentCode);
	}

	void Shader::Validate()
	{
		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		glValidateProgram(shaderID);
		glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
			printf("Error validating program: '%s'\n", eLog);
			return;
		}
	}

	GLuint Shader::GetProjectionLocation()
	{
		return uniformProjection;
	}

	GLuint Shader::GetModelLocation()
	{
		return uniformModel;
	}

	GLuint Shader::GetViewLocation()
	{
		return uniformView;
	}

	GLuint Shader::GetAmbientIntensityLocation()
	{
		return m_UniformDirectionalLight.UniformAmbientIntensity;
	}

	GLuint Shader::GetAmbientColourLocation()
	{
		return m_UniformDirectionalLight.UniformColour;
	}

	GLuint Shader::GetDiffuseIntensityLocation()
	{
		return m_UniformDirectionalLight.UniformDiffuseIntensity;
	}

	GLuint Shader::GetDiffuseDirectionLocation()
	{
		return m_UniformDirectionalLight.UniformDirection;
	}

	GLuint Shader::GetMatSpecularIntensityLocation()
	{
		return uniformMatSpecularIntensity;
	}

	GLuint Shader::GetMatShininessLocation()
	{
		return uniformMatShininess;
	}

	GLuint Shader::GetCameraPositionLocation()
	{
		return uniformCameraPosition;
	}

	GLuint Shader::GetOmniLightPosLocation()
	{
		return uniformOmniLightPos;
	}

	GLuint Shader::GetFarPlaneLocation()
	{
		return uniformFarPlane;
	}

	void Shader::SetDirectionalLight(DirectionalLight* dLight)
	{
		dLight->UseLight(m_UniformDirectionalLight.UniformAmbientIntensity, m_UniformDirectionalLight.UniformColour, m_UniformDirectionalLight.UniformDiffuseIntensity, m_UniformDirectionalLight.UniformDirection);
	}

	void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset)
	{
		if (lightCount > MAX_POINT_LIGHTS)
		{
			printf("\nMAX POINT LIGHT LIMIT REACHEAD!");
			lightCount = MAX_POINT_LIGHTS;
		}

		glUniform1i(m_UniformPointLightCount, lightCount);

		for (size_t i = 0; i < lightCount; i++)
		{
			pLight[i].UseLight(m_UniformPointLights[i].UniformAmbientIntensity, m_UniformPointLights[i].UniformColour, m_UniformPointLights[i].UniformDiffuseIntensity,
				m_UniformPointLights[i].UniformPosition, m_UniformPointLights[i].UniformConstant, m_UniformPointLights[i].UniformLinear, m_UniformPointLights[i].UniformExponent, m_UniformPointLights[i].UniformUseOmniShadow);

			if (pLight[i].GetShadowMap() != nullptr)
			{
				pLight[i].GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + i);
				glUniform1i(m_UniformOmniShadowMap[i + offset].ShadowMap, textureUnit + i);
				glUniform1f(m_UniformOmniShadowMap[i + offset].FarPlane, pLight[i].GetFarPlane());
			}

		}
	}

	void Shader::SetSpotLights(SpotLight* sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset)
	{
		if (lightCount > MAX_SPOT_LIGHTS)
		{
			printf("\nMAX SPOT LIGHT LIMIT REACHEAD!");
			lightCount = MAX_SPOT_LIGHTS;
		}

		glUniform1i(m_UniformSpotLightCount, lightCount);

		for (size_t i = 0; i < lightCount; i++)
		{
			sLight[i].UseLight(m_UniformSpotLights[i].UniformAmbientIntensity, m_UniformSpotLights[i].UniformColour, m_UniformSpotLights[i].UniformDiffuseIntensity,
				m_UniformSpotLights[i].UniformPosition, m_UniformSpotLights[i].UniformDirection, m_UniformSpotLights[i].UniformConstant, m_UniformSpotLights[i].UniformLinear, m_UniformSpotLights[i].UniformExponent, m_UniformSpotLights[i].UniformUseOmniShadow, m_UniformSpotLights[i].UniformEdge);

			if (sLight[i].GetShadowMap() != nullptr)
			{
				sLight[i].GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + i);
				glUniform1i(m_UniformOmniShadowMap[i + offset].ShadowMap, textureUnit + i);
				glUniform1f(m_UniformOmniShadowMap[i + offset].FarPlane, sLight[i].GetFarPlane());
			}
		}
	}

	void Shader::SetTextureUnit(GLuint textureUnit)
	{
		glUniform1i(uniformTexture, textureUnit);
	}

	void Shader::SetDirectionalShadowMap(GLuint textureUnit)
	{
		glUniform1i(uniformDirectionalShadowMap, textureUnit);
	}

	void Shader::SetDirectionalLightTransform(glm::mat4* lightTransform)
	{
		glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(*lightTransform));
	}

	void Shader::SetLightMatrices(std::vector<glm::mat4> lightMatrices)
	{
		for (size_t i = 0; i < 6; i++)
		{
			glUniformMatrix4fv(uniformLightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
		}
	}

	void Shader::SetUseDirLightShadow(bool active)
	{
		UseShader();
		glUniform1i(glGetUniformLocation(shaderID, "useDirLightShadow"), (int)active);
	}

	void Shader::UseShader()
	{
		glUseProgram(shaderID);
	}

	void Shader::ClearShader()
	{
		if (shaderID != 0)
		{
			glDeleteProgram(shaderID);
			shaderID = 0;
		}
		uniformModel = 0;
		uniformProjection = 0;
		uniformView = 0;
	}

	Shader::~Shader()
	{
		ClearShader();
	}

	std::string Shader::ReadFile(const char* fileLocation)
	{
		std::string content;
		std::ifstream fileStream(fileLocation, std::ios::in);

		if (!fileStream.is_open())
		{
			printf("Failed to read %sl File doesn't exist.", fileLocation);
			return "";
		}

		std::string line = "";

		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}

	void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
	{
		shaderID = glCreateProgram();

		if (!shaderID)
		{
			printf("Error creating shader program!\n");
			return;
		}

		AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
		AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);


		CompileProgram();
	}

	void Shader::CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
	{
		shaderID = glCreateProgram();

		if (!shaderID)
		{
			printf("Error creating shader program!\n");
			return;
		}

		AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
		AddShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
		AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

		CompileProgram();
	}

	void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
	{
		GLuint theShader = glCreateShader(shaderType);

		const GLchar* theCode[1];
		theCode[0] = shaderCode;

		GLint codeLength[1];
		codeLength[0] = strlen(shaderCode);

		glShaderSource(theShader, 1, theCode, codeLength);
		glCompileShader(theShader);

		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
			printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
			return;
		}

		glAttachShader(theProgram, theShader);
	}

	void Shader::CompileProgram()
	{
		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
			printf("Error linking program: '%s'\n", eLog);
			return;
		}

		//glValidateProgram(shaderID);
		//glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
		//if (!result)
		//{
		//	glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		//	printf("Error validating program: '%s'\n", eLog);
		//	return;
		//}

		uniformModel = glGetUniformLocation(shaderID, "model");
		uniformProjection = glGetUniformLocation(shaderID, "projection");
		uniformView = glGetUniformLocation(shaderID, "view");

		m_UniformDirectionalLight.UniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
		m_UniformDirectionalLight.UniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
		m_UniformDirectionalLight.UniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
		m_UniformDirectionalLight.UniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");

		uniformMatShininess = glGetUniformLocation(shaderID, "material.shininess");
		uniformMatSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
		uniformCameraPosition = glGetUniformLocation(shaderID, "cameraPosition");

		m_UniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

		for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			char locBuff[100] = { '\0' };
			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
			m_UniformPointLights[i].UniformColour = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
			m_UniformPointLights[i].UniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
			m_UniformPointLights[i].UniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
			m_UniformPointLights[i].UniformPosition = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
			m_UniformPointLights[i].UniformConstant = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
			m_UniformPointLights[i].UniformLinear = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
			m_UniformPointLights[i].UniformExponent = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].useOmniShadow", i);
			m_UniformPointLights[i].UniformUseOmniShadow = glGetUniformLocation(shaderID, locBuff);
		}

		m_UniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");

		for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
		{
			//SpotLight inherited from PointLight
			char locBuff[100] = { '\0' };
			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.colour", i);
			m_UniformSpotLights[i].UniformColour = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
			m_UniformSpotLights[i].UniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
			m_UniformSpotLights[i].UniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
			m_UniformSpotLights[i].UniformPosition = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
			m_UniformSpotLights[i].UniformConstant = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
			m_UniformSpotLights[i].UniformLinear = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
			m_UniformSpotLights[i].UniformExponent = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.useOmniShadow", i);
			m_UniformSpotLights[i].UniformUseOmniShadow = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
			m_UniformSpotLights[i].UniformDirection = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
			m_UniformSpotLights[i].UniformEdge = glGetUniformLocation(shaderID, locBuff);
		}

		uniformTexture = glGetUniformLocation(shaderID, "theTexture");
		uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
		uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");

		uniformOmniLightPos = glGetUniformLocation(shaderID, "lightPos");
		uniformFarPlane = glGetUniformLocation(shaderID, "farPlane");

		for (size_t i = 0; i < 6; i++)
		{
			char locBuff[100] = { '\0' };
			snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
			uniformLightMatrices[i] = glGetUniformLocation(shaderID, locBuff);
		}
		for (size_t i = 0; i < MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS; i++)
		{
			char locBuff[100] = { '\0' };

			snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].shadowMap", i);
			m_UniformOmniShadowMap[i].ShadowMap = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].farPlane", i);
			m_UniformOmniShadowMap[i].FarPlane = glGetUniformLocation(shaderID, locBuff);
		}
	}
}