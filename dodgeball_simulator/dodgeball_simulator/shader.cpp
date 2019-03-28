#include "shader.h"

//Generate Object
GLuint programID;

shader::shader()
{
	unsigned int shader_id = glCreateShader(GL_SHADER_TYPE);

}



bool shader::loadShader (const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
	
	unsigned int buffer;

	//create a buffer
	glGenBuffers(1, &buffer);

	//bind the buffer to vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);


	//Vertex shader anbinden
	std::ifstream is_vs("vertexShaderFile");
	const std::string f_vertshad((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());

	//Fragment shader anbinden
	std::ifstream is_fs("fragmentShaderFile");
	const std::string f_fragshad((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());


	//Generate Vertex Shader Object
	GLuint vert_shad = glCreateShader(GL_VERTEX_SHADER);

	//Generate Fragment Shader Object
	GLuint frag_shad = glCreateShader(GL_FRAGMENT_SHADER);


	//Load Source Code Vertex Shader
	const char* codePtr_vert = f_vertshad.c_str();
	glShaderSource(vert_shad, 1, &codePtr_vert, NULL);
	glCompileShader(vert_shad);

	//Load Source Code Fragment Shader
	const char* codePtr_frag = f_fragshad.c_str();
	glShaderSource(frag_shad, 1, &codePtr_frag, NULL);
	glCompileShader(frag_shad);


	//Check for errors Vertex Shader
	GLint succeded_vertsh;
	glGetShaderiv(vert_shad, GL_COMPILE_STATUS, &succeded_vertsh);
	if (succeded_vertsh == GL_FALSE)
	{
		//Log auslesen und ausgeben
		GLint logSize;
		glGetShaderiv(vert_shad, GL_INFO_LOG_LENGTH, &logSize);
		GLchar* message = new char[logSize];
		glGetShaderInfoLog(vert_shad, logSize, NULL, message);
		delete[] message;
	}

	//Check for errors Fragment Shader
	GLint succeded_fragsh;
	glGetShaderiv(frag_shad, GL_COMPILE_STATUS, &succeded_fragsh);
	if (succeded_fragsh == GL_FALSE)
	{
		//Log auslesen und ausgeben
		GLint logSize;
		glGetShaderiv(frag_shad, GL_INFO_LOG_LENGTH, &logSize);
		GLchar* message = new char[logSize];
		glGetShaderInfoLog(frag_shad, logSize, NULL, message);
		delete[] message;
	}

	//Generate Object
	GLuint programID = glCreateProgram();

	//Attach Shader Objects
	glAttachShader(programID, vert_shad);
	glAttachShader(programID, frag_shad);

	glLinkProgram(programID);
	glValidateProgram(programID);


	//Check Errors
	GLint succeded;
	glGetProgramiv(programID, GL_LINK_STATUS, &succeded);
	if (!succeded)
	{
		//Log auslesen und ausgeben
		GLint logSize;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);
		GLchar* message = new char[logSize];
		glGetProgramInfoLog(programID, logSize, NULL, message);
		delete[] message;
	}

	 
	//Delete Vertex Shader Object before exit
	glDeleteShader(vert_shad);

	//Delete Fragment Shader Object before exit
	glDeleteShader(frag_shad);




	return true;

}

void shader::useShader()
{
	glUseProgram(programID);
}

void shader::deleteShader()
{
	glDeleteProgram(programID);
}

shader::~shader()
{
}
