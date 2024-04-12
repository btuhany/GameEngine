#version 330														
																	
layout (location = 0) in vec3 pos;						
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;
		
uniform mat4 model;	
uniform mat4 projection;
uniform mat4 view;

out vec4 vCol;
out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

void main()		
{	
	gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
	vCol = vec4(clamp(pos, 0.0, 1.0), 1.0f);	
	TexCoords = tex;
	Normal = mat3(transpose(inverse(model))) * norm; //?  //invert the scaling
	FragPos = (model * vec4(pos, 1.0)).xyz;
}	

