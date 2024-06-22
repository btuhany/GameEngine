#version 330								
																	
in vec4 vCol;		
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

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
	bool useOmniShadow;
};
struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};
struct OmniShadowMap
{
	samplerCube shadowMap;
	float farPlane;
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

uniform bool useDirLightShadow;

uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;
uniform OmniShadowMap omniShadowMaps[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

uniform Material material;

uniform vec3 cameraPosition; //eyePosition

vec3 sampleOffsetDirections[20] = vec3[]
(
	vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
	vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
	vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
	vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
	vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

float CalcDirectionalShadowFactor(DirectionalLight dLight)
{
	if (!useDirLightShadow)
		return 0.0;

	vec3 projCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w;  //projCoords will be between -1.0 - 1.0
	projCoords = (projCoords * 0.5) + 0.5; //0.0 - 1.0

	float closesDepth = texture(directionalShadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(dLight.direction);

	float bias = max(0.2 * (1.0 - dot(-normal, lightDir)), 0.005);

	float shadow = 0.0;

	vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x,y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;

		}
	}
	shadow /= 9.0;

	if (projCoords.z > 1.0)
	{
		shadow = 0.0;
	}

	return shadow;
}

float CalcOmniShadowFactor(PointLight light, int shadowIndex)
{
	if (!light.useOmniShadow)
	{
		return 0.0f;
	}
	vec3 fragToLight = FragPos - light.position;
	float currentDepth = length(fragToLight);

	float shadow = 0.0;
	float bias = 0.05;
	int samples = 20;

	//we can set the diskRadius to 0.01 ideally. Here we are calculating the shadow radius according to camera pos.
	float viewDistance = length(cameraPosition - FragPos);
	float diskRadius = (1.0 + (viewDistance / omniShadowMaps[shadowIndex].farPlane)) / 25.0;


	for(int i = 0; i < samples; i++)
	{
		float closestDepth = texture(omniShadowMaps[shadowIndex].shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
		closestDepth *= omniShadowMaps[shadowIndex].farPlane;
		if (currentDepth - bias > closestDepth)
		{
			shadow += 1.0f;
		}
	}

	shadow /= float(samples);
	return shadow;
}

vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor)
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
	return (ambientColour + (1.0 - shadowFactor) * (diffuseColour + specularColour));    
}

vec4 CalcDirectionalLight()
{
	float shadowFactor = CalcDirectionalShadowFactor(directionalLight);
	return CalcLightByDirection(directionalLight.base, -directionalLight.direction, shadowFactor);  // 0 - directionalLight direction
}

vec4 CalcPointLight(PointLight pLight, int shadowIndex)
{
	vec3 direction = pLight.position - FragPos;
	float distance = length(direction);
	direction = normalize(direction);

	float shadowFactor = CalcOmniShadowFactor(pLight, shadowIndex);

	vec4 colour = CalcLightByDirection(pLight.base, direction, shadowFactor);
	float attenuation = pLight.exponent * distance * distance + pLight.linear * distance + pLight.constant;
	return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight, int shadowIndex)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position); //from source to FragPos
	float slFactor = dot(rayDirection, sLight.direction);

	if (slFactor > sLight.edge)
	{
		vec4 colour = CalcPointLight(sLight.base, shadowIndex);
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
		totalColour += CalcSpotLight(spotLights[i], i + pointLightCount);
	}
	return totalColour;
}

vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0.0, 0.0, 0.0, 1.0);
	for(int i = 0; i < pointLightCount; i++)
	{
		totalColour += CalcPointLight(pointLights[i], i);
	}
	return totalColour;
}

void main()								
{			
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLights();
	finalColour += CalcSpotLights();
	colour = texture(theTexture, TexCoords) * finalColour;     
	//colour = vec4(normalize(Normal), 1.0);    
}	