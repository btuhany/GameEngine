#version 330								
											
out vec4 colour;							
											
in vec4 vCol;		
in vec2 TexCoords;
in vec3 Normal;

struct DirectionalLight {
	vec3 colour;
	float ambientIntensity;
	vec3 diffuseDirection;
	float diffuseIntensity;
};

uniform sampler2D texture2D;
uniform DirectionalLight directionalLight;

void main()								
{			
	//ambient lighting
	vec4 ambientColor = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
	//diffuse lighting
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.diffuseDirection)), 0.0f);  //0.0f - 1.0f
	vec4 diffuseColor = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

	colour = texture(texture2D, TexCoords) * (ambientColor + diffuseColor);     
}	