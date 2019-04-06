#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include "shader.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Zeile 32!!

using namespace std;

struct Texture {
	unsigned int id;
	string type;
	string path;  // we store the path of the texture to compare with other textures
};

vector<Texture> textures_loaded;

Assimp::Importer importer;
//const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);


class model
{
public:
	/*  Functions   */
	model(char *path)
	{
		loadModel(path);
	}
	void Draw(shader shader);
private:
	/*  Model Data  */
	vector<mesh> meshes;
	string directory;
	/*  Functions   */
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
};






/*class model
{
public:
	model();
	~model();
};*/

