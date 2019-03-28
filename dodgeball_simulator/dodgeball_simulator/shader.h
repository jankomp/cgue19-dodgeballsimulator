#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>

class shader
{
public:
	shader();
	~shader();

	bool loadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	
	void useShader();
	void deleteShader();

};

