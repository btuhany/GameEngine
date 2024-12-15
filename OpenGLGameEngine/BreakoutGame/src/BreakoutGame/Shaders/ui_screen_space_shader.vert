#version 330														
																	
layout (location = 0) in vec3 pos;						
layout (location = 1) in vec2 tex;
		
uniform mat4 model;	
uniform mat4 projection;
uniform mat4 view;

out vec2 TexCoords;

void main()		
{	
	gl_Position = projection * vec4(pos.x, pos.y, pos.z, 1.0);
	TexCoords = tex;
}	

