#version 330								
											
out vec4 colour;							
											
in vec4 vCol;		
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct DirectionalLight 
{
	vec3 colour;
	float ambientIntensity;
	vec3 diffuseDirection;
	float diffuseIntensity;
};

struct Material	
{
	float specularIntensity;
	float shininess;
};

uniform sampler2D texture2D;
uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 cameraPosition; //eyePosition

void main()								
{			
	//ambient lighting
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
	//diffuse lighting
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.diffuseDirection)), 0.0f);  //0.0f - 1.0f
	vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
	
	vec4 specularColour = vec4(0.0f);

	if (diffuseFactor > 0.0f)
	{
		vec3 fragPosToEye = normalize(cameraPosition - FragPos);
		vec3 reflectedVector = normalize(reflect(directionalLight.diffuseDirection, normalize(Normal)));

		float specularFactor = dot(reflectedVector, fragPosToEye);

		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(directionalLight.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}



	colour = texture(texture2D, TexCoords) * (ambientColour + diffuseColour + specularColour);     
}	