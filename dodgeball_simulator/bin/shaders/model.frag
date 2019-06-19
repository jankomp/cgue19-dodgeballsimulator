#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D lightMap;
uniform float settingsBrightness;

void main()
{    

	vec4 lightMapColor = texture(lightMap, TexCoords);
	vec4 newLightMapColor = lightMapColor / 4;
    FragColor = texture(texture_diffuse1, TexCoords) + newLightMapColor;
}