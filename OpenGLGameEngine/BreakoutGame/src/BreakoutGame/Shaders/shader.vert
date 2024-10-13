#version 330														
																	
layout (location = 0) in vec4 vertex;						
		
uniform mat4 model;	
uniform mat4 projection;
uniform mat4 view;

out vec2 TexCoords;

void main()		
{	
	TexCoords = vertex.zw;
	gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}	

