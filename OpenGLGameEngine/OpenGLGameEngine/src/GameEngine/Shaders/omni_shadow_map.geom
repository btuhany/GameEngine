#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 lightMatrices[6];

out vec4 FragPos;

void main()
{
	for(int i = 0; i < 6; i++)   //i = face
	{
		gl_Layer = i;
		for(int j = 0; j < 3; j++)
		{
			FragPos = gl_in[j].gl_Position;
			gl_Position = lightMatrices[i] * FragPos;
			EmitVertex();
		}
		EndPrimitive();
	}
}