#version 330								
																	
in vec2 TexCoords;
out vec4 colour;							
					
uniform sampler2D theTexture;

void main()								
{			
	colour = texture(theTexture, TexCoords);      
}	