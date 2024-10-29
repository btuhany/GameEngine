#version 330								
																	
in vec4 vCol;		
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

out vec4 colour;							
					
struct Material	
{
	float specularIntensity;
	float shininess;
};

uniform sampler2D theTexture;
uniform Material material;

void main()								
{			
	colour = vec4(0.0, 1.0, 0.0, 1.0);   
}	