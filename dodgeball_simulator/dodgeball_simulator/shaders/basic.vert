#version 430 core

in vec4 position;

out vec4 vertexColor;

void main() {

	gl_Position = position;
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
	
}