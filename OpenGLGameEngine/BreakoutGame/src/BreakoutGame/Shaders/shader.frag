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

uniform vec3 cameraPosition;

void main()								
{			
	colour = texture(theTexture, TexCoords);      
}	