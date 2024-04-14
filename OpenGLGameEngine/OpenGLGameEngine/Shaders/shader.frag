#version 330								
																	
in vec4 vCol;		
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;							
					
const int MAX_POINT_LIGHTS = 8;
const int MAX_SPOT_LIGHTS = 5;

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};
struct PointLight 
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};
struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};
struct DirectionalLight 
{
	Light base;
	vec3 direction;
};
struct Material	
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D texture2D;
uniform Material material;

uniform vec3 cameraPosition; //eyePosition

vec4 CalcLightByDirection(Light light, vec3 direction)
{
	//ambient lighting
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	//diffuse lighting
	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);  //0.0f - 1.0f

	vec4 diffuseColour = vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColour = vec4(0.0f);

	if (diffuseFactor > 0.0f)
	{
		vec3 fragPosToEye = normalize(FragPos - cameraPosition);  //for reflecting
		vec3 reflectedVector = normalize(reflect(direction, normalize(Normal)));

		float specularFactor = dot(reflectedVector, fragPosToEye);

		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);

			specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}
	return (ambientColour + diffuseColour + specularColour);    
}

vec4 CalcDirectionalLight()
{
	return CalcLightByDirection(directionalLight.base, -directionalLight.direction);  // 0 - directionalLight direction
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = pLight.position - FragPos;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 colour = CalcLightByDirection(pLight.base, direction);
	float attenuation = pLight.exponent * distance * distance + pLight.linear * distance + pLight.constant;
	return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position); //from source to FragPos
	float slFactor = dot(rayDirection, sLight.direction);

	if (slFactor > sLight.edge)
	{
		vec4 colour = CalcPointLight(sLight.base);
		return colour * (1.0f - (1.0f - slFactor) * (1.0f/(1.0f - sLight.edge)));
	}
	else
	{
		return vec4(0.0, 0.0, 0.0, 1.0);
	}
}

vec4 CalcSpotLights()
{
	vec4 totalColour = vec4(0.0, 0.0, 0.0, 1.0);
	for(int i = 0; i < spotLightCount; i++)
	{
		totalColour += CalcSpotLight(spotLights[i]);
	}
	return totalColour;
}

vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0.0, 0.0, 0.0, 1.0);
	for(int i = 0; i < pointLightCount; i++)
	{
		totalColour += CalcPointLight(pointLights[i]);
	}
	return totalColour;
}

void main()								
{			
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLights();
	finalColour += CalcSpotLights();
	colour = texture(texture2D, TexCoords) * finalColour;     
	//colour = vec4(normalize(Normal), 1.0);    
}	