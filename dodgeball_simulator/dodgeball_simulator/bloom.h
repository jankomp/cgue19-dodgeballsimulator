#pragma once
//#include "shader.h"
#include "window.h"
#include <vector>
#include "Camera.h"

class Bloom
{
public:
	Bloom();
	~Bloom();
	void framebuffer();
	void setLight();
	void render(Shader *blurShader, Shader *bloomShader, Shader *lightShader, Shader *bloom2Shader, glm::mat4 projection, glm::mat4 view, unsigned int woodText, Camera *camera);
	void render2(Shader *blurShader, Shader *bloomShader, Shader *lightShader, Shader *bloom2Shader, glm::mat4 projection, glm::mat4 view);
	//void render();
	void renderCube();
	void renderQuad();
	void bind1();
	void bind2();


private:
	unsigned int colorBuffers[2];
	bool horizontal = true;
	bool first_iteration = true;
	unsigned int amount = 10;
	unsigned int pingpongFBO[2];
	unsigned int pingpongColorbuffers[2];
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	bool bloom = true;
	bool bloomKeyPressed = false;
	float exposure = 1.0f;
	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightColors;

	GLuint fbo;
	


};

