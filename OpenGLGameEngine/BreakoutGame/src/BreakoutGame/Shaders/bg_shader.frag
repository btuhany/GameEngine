#version 330								
																	
in vec4 vCol;		
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

out vec4 colour;							
					
uniform float iTime;
uniform sampler2D theTexture;


void main()								
{			
    vec2 uv = TexCoords;

    float wave1 = sin(uv.y * 5.0 + iTime * 1.0) * 0.01;
    float wave2 = cos(uv.y * 15.0 - iTime * 1.0) * 0.02;
    vec2 distortedUV = uv + vec2(wave1, wave2);

    vec4 textureColor = texture(theTexture, distortedUV);

    vec3 neonColor = vec3(0.0);
    neonColor.r = 0.7 + 0.7 * sin(uv.x * 10.0 + iTime * 0.3);
    neonColor.g = 0.2 + 0.2 * cos(uv.y * 10.0 - iTime * 0.8);
    neonColor.b = 0.4 + 0.7 * sin(uv.x * 10.0 - uv.y * 3.0 + iTime * 0.3);

    vec3 finalColor = mix(textureColor.rgb, neonColor, 0.5);

    colour = vec4(finalColor, 1.0) * 0.6;  
}	