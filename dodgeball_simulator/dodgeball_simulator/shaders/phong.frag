#version 430 core
/*
* Copyright 2018 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/

in vec3 Normal;  
in vec3 FragPos;

uniform vec3 viewPos; 
uniform vec3 directionalLightCol;
uniform vec3 directionalLightDir;
uniform vec3 pointLightPos;
uniform vec3 pointLightCol;
uniform vec3 pointLightAtt;
uniform vec3 objectColor;
uniform vec4 illumination;

out vec4 color;

void main() {	

	vec3 normalNorm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// Directional Light
	vec3 dirLightDirNorm = normalize(directionalLightDir);

	vec3 dirLightRef = reflect(dirLightDirNorm, normalNorm);
	vec3 dirLightDiffuse = directionalLightCol * illumination.y * max(dot(normalNorm, -dirLightDirNorm), 0);
	vec3 dirLightSpecular = directionalLightCol * illumination.z * pow(max(dot(viewDir, dirLightRef), 0), illumination.w);

	// Point Light

	vec3 pointLightDir = normalize(FragPos - pointLightPos);
	vec3 pointLightRef = normalize(reflect(pointLightDir, normalNorm));
	float pointLightDist = length(pointLightPos - FragPos);
	float pointLightAtt = 1 / (pointLightAtt.x + pointLightAtt.y * pointLightDist + pointLightAtt.z * pow(pointLightDist, 2));
	vec3 pointLightDiffuse = pointLightCol * pointLightAtt * illumination.y * max(dot(normalNorm, -pointLightDir), 0);
	vec3 pointLightSpecular = pointLightCol * pointLightAtt * illumination.z * pow(max(dot(viewDir, pointLightRef), 0), illumination.w);

	vec3 ambient = vec3(1, 1, 1) * illumination.x;
	vec3 diffuse = dirLightDiffuse + pointLightDiffuse;
	vec3 specular = dirLightSpecular + pointLightSpecular;

	vec3 result = objectColor * (ambient + diffuse + specular);
	color = vec4(result,1);


}