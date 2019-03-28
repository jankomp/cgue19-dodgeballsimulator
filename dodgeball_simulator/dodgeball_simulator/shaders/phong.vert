#version 430 core
/*
* Copyright 2018 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/

layout(location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;

uniform mat4 viewProjMatrix;
uniform mat4 modelMatrix;

out vec3 FragPos;
out vec3 Normal; 

void main() {

	FragPos = vec3(modelMatrix * vec4(position, 1.0));
    Normal = aNormal;  
	
	gl_Position = viewProjMatrix * modelMatrix * vec4(position, 1);
}