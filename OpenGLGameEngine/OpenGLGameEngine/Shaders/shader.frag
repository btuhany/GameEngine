#version 330								
																	
in vec4 vCol;		
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;							
					
const int MAX_POINT_LIGHTS = 8;

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

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

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

vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0.0, 0.0, 0.0, 1.0);
	for(int i = 0; i < pointLightCount; i++)
	{
		vec3 direction = pointLights[i].position - FragPos;
		float distance = length(direction);
		direction = normalize(direction);

		vec4 colour = CalcLightByDirection(pointLights[i].base, direction);
		float attenuation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;
		totalColour += (colour / attenuation);
	}
	return totalColour;
}

void main()								
{			
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLights();
	colour = texture(texture2D, TexCoords) * finalColour;     
	//colour = vec4(normalize(Normal), 1.0);    
}	