#version 430 core
/*
* Copyright 2018 Vienna University of Technology.
* Institute of Computer Graphics and Algorithms.
* This file is part of the ECG Lab Framework and must not be redistributed.
*/

in vec3 lightCol;

uniform vec3 objectColor;

out vec4 color;

void main() {	
	color = vec4(lightCol * objectColor, 1);
}