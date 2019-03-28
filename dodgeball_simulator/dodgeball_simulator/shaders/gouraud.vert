#version 430 core
/*
* Copyright 2018 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/

layout(location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal; 

uniform mat4 modelMatrix;
uniform mat4 viewProjMatrix;
uniform vec3 viewPos; 
uniform vec3 directionalLightCol;
uniform vec3 directionalLightDir;
uniform vec3 pointLightPos;
uniform vec3 pointLightCol;
uniform vec3 pointLightAtt;
uniform vec4 illumination;


out vec3 lightCol; // resulting color from lighting calculations

void main() {

	vec3 transformedNormal = mat3(transpose(inverse(modelMatrix))) * aNormal;
	vec3 normalNorm = normalize(transformedNormal);

	vec3 fragPos = vec3(modelMatrix * vec4(position, 1.0));
	vec3 viewDir = normalize(viewPos - fragPos);

	// Directional Light
	vec3 dirLightDirNorm = normalize(directionalLightDir);

	vec3 dirLightRef = reflect(dirLightDirNorm, normalNorm);
	vec3 dirLightDiffuse = directionalLightCol * illumination.y * max(dot(normalNorm, -dirLightDirNorm), 0);
	vec3 dirLightSpecular = directionalLightCol * illumination.z * pow(max(dot(viewDir, dirLightRef), 0), illumination.w);

	// Point Light

	vec3 pointLightDir = normalize(fragPos - pointLightPos);
	vec3 pointLightRef = normalize(reflect(pointLightDir, normalNorm));
	float pointLightDist = length(pointLightPos - fragPos);
	float pointLightAttenuation = 1 / (pointLightAtt.x + pointLightAtt.y * pointLightDist + pointLightAtt.z * pow(pointLightDist, 2));
	vec3 pointLightDiffuse = pointLightCol * pointLightAttenuation * illumination.y * max(dot(normalNorm, -pointLightDir), 0);
	vec3 pointLightSpecular = pointLightCol * pointLightAttenuation * illumination.z * pow(max(dot(viewDir, pointLightRef), 0), illumination.w);

	vec3 ambient = vec3(1, 1, 1) * illumination.x;
	vec3 diffuse = dirLightDiffuse + pointLightDiffuse;
	vec3 specular = dirLightSpecular + pointLightSpecular;


	lightCol =  (ambient + diffuse + specular);
	gl_Position = viewProjMatrix * modelMatrix * vec4(position, 1);

}