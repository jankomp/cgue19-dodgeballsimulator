#include "square.h"


square::square(float height, float length) 
{
	this->height = height;
	this->length = length;

	


	unsigned int buffer;

	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	


}

std::vector<GLfloat> square::calcVertices() {

	return std::vector<GLfloat> {

		height / 2.0f, length / 2.0f,
		height / 2.0f, -length / 2.0f,
		-height / 2.0f, -length / 2.0f,
		-height / 2.0f, length / 2.0f


	};

}


void square::draw() 
{
	glDrawArrays(GL_TRIANGLES, 0, 2);
	//glDrawElements(GL_TRIANGLES, _elements, GL_UNSIGNED_INT, 0);

}


square::~square()
{
}
