//
//#pragma once
//
//#include <stdio.h>
//
//#include <vector>
//#include <algorithm>
//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include "Shader.h"
//
//using namespace glm;
//
//// CPU representation of a particle
//struct Particle {
//	glm::vec3 pos, speed;
//	unsigned char r, g, b, a; // Color
//	float size, angle, weight;
//	float life; // Remaining life of the particle. if <0 : dead and unused.
//	float cameradistance; // *Squared* distance to the camera. if dead : -1.0f
//
//	bool operator<(const Particle& that) const {
//		// Sort in reverse order : far particles drawn first.
//		return this->cameradistance > that.cameradistance;
//	}
//};
//
//class ParticleCreation
//{
//public:
//	ParticleCreation();
//	int findUnusedParticle();
//	void sortParticles();
//	void loadParticle();
//	void calculateParticle(float deltaTime, glm::mat4 view, glm::mat4 projectionView, Shader particleShader);
//	void deleteEverything();
//	GLuint loadDDS(const char * imagepath);
//
//private:
//
//	GLuint VertexArrayID;
//	GLuint Texture;
//	const int MaxParticles = 5000;
//	Particle ParticlesContainer[5000];
//	int LastUsedParticle = 0;
//	GLfloat* g_particule_position_size_data;
//	GLubyte* g_particule_color_data;
//	GLuint billboard_vertex_buffer;
//	GLuint particles_position_buffer;
//	GLuint particles_color_buffer;
//
//};







#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H
//
#include <stdio.h>
//#include <stdlib.h>

#include <vector>
#include <algorithm>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

using namespace glm;

#include "shader.h"


// CPU representation of a particle
struct Particle {
	glm::vec3 pos, speed;
	unsigned char r, g, b, a; // Color
	float size, angle, weight;
	float life; // Remaining life of the particle. if <0 : dead and unused.
	float cameradistance; // *Squared* distance to the camera. if dead : -1.0f

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};

class ParticleGenerator
{
public:
	ParticleGenerator();
	GLuint loadDDS(const char * imagepath);
	int FindUnusedParticle();
	void SortParticles();
	void setVBO(Shader shader, glm::mat4 ProjectionMatrix);
	void render(float delta, Shader shader, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);
	void del();
	void calculateParticle(float deltaTime, glm::mat4 view, glm::mat4 projectionView, Shader particleShader);

private:
	GLuint Texture;
	const int MaxParticles = 5000;
	Particle ParticlesContainer[5000];
	int LastUsedParticle = 0;

	GLfloat* g_particule_position_size_data;
	GLubyte* g_particule_color_data;
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLuint billboard_vertex_buffer;
	GLuint VertexArrayID;

};

#endif