#include "geometry.h"

//geometry::geometry(glm::mat4 modelMatrix, geometryData& data, std::shared_ptr<Material> material)
	//: _elements(data.indices.size()), _modelMatrix(modelMatrix), _material(material)


geometry::geometry(glm::mat4 modelMatrix, geometryData& data, glm::vec3 color)
	: _elements(data.indices.size()), _modelMatrix(modelMatrix)
{
	// create VAO
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// create positions VBO
	glGenBuffers(1, &_vboPositions);
	glBindBuffer(GL_ARRAY_BUFFER, _vboPositions);
	glBufferData(GL_ARRAY_BUFFER, data.positions.size() * sizeof(glm::vec3), data.positions.data(), GL_STATIC_DRAW);

	// bind positions to location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// create normals VBO
	glGenBuffers(1, &_vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
	glBufferData(GL_ARRAY_BUFFER, data.normals.size() * sizeof(glm::vec3), data.normals.data(), GL_STATIC_DRAW);

	// bind normals to location 1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// create and bind uv VBO
	glGenBuffers(1, &_vboUv);
	glBindBuffer(GL_ARRAY_BUFFER, _vboUv);
	glBufferData(GL_ARRAY_BUFFER, data.uv.size() * sizeof(glm::vec2), data.uv.data(), GL_STATIC_DRAW);

	// bind uvs to location 2
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//ANSCHAUEN!!!

	// create and bind indices VBO
	glGenBuffers(1, &_vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(unsigned int), data.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}


geometry::~geometry()
{
	glDeleteBuffers(1, &_vboPositions);
	glDeleteBuffers(1, &_vboNormals);
	glDeleteBuffers(1, &_vboUv);
	glDeleteBuffers(1, &_vboIndices);

	glDeleteVertexArrays(1, &_vao);
}


void geometry::draw()
{
	//shader shader = _material->getShader();
	//shader.useShader();

	//shader->setUniform("modelMatrix", _modelMatrix);
	//shader->setUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(_modelMatrix))));

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _elements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void geometry::transform(glm::mat4 transformation)
{
	_modelMatrix = transformation * _modelMatrix;
}

void geometry::resetModelMatrix()
{
	_modelMatrix = glm::mat4(1);
}


geometryData geometry::createCubeGeometry(float width, float height, float depth)
{
	geometryData data;

	data.positions = {
		// front
		glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f),
		// back
		glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f),
		// right
		glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f),
		// left
		glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f),
		// top
		glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f),
		// bottom
		glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f)
	};

	data.normals = {
		// front
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		// back
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		// right
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		// left
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		// top
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		// bottom
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0)
	};

	data.uv = {

		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(0, 1),

		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(0, 1),

		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(0, 1),

		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(0, 1),

		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(0, 1),

		glm::vec2(0, 0),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(0, 1),

	};


	data.indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		4, 5, 6,
		6, 7, 4,
		// right
		8, 9, 10,
		10, 11, 8,
		// left
		12, 13, 14,
		14, 15, 12,
		// top
		16, 17, 18,
		18, 19, 16,
		// bottom
		20, 21, 22,
		22, 23, 20
	};




	return std::move(data);
}

geometryData geometry::createCylinderGeometry(unsigned int segments, float height, float radius)
{
	geometryData data;


	// center vertices
	data.positions.push_back(glm::vec3(0, -height / 2.0f, 0));
	data.normals.push_back(glm::vec3(0, -1, 0));
	data.positions.push_back(glm::vec3(0, height / 2.0f, 0));
	data.normals.push_back(glm::vec3(0, 1, 0));
	data.uv.push_back(glm::vec2(0.5, 0.5));
	data.uv.push_back(glm::vec2(0.5, 0.5));

	// circle segments
	float angle_step = 2.0f * glm::pi<float>() / float(segments);
	for (unsigned int i = 0; i < segments; i++) {
		glm::vec3 circlePos = glm::vec3(
			glm::cos(i * angle_step) * radius,
			-height / 2.0f,
			glm::sin(i * angle_step) * radius
		);

		// bottom ring vertex
		data.positions.push_back(circlePos);
		data.positions.push_back(circlePos);
		data.normals.push_back(glm::vec3(0, -1, 0));
		data.normals.push_back(glm::normalize(circlePos - glm::vec3(0, -height / 2.0f, 0)));


		// top ring vertex
		circlePos.y = height / 2.0f;
		data.positions.push_back(circlePos);
		data.positions.push_back(circlePos);
		data.normals.push_back(glm::vec3(0, 1, 0));
		data.normals.push_back(glm::normalize(circlePos - glm::vec3(0, height / 2.0f, 0)));


		// bottom face
		data.indices.push_back(0);
		data.indices.push_back(2 + i * 4);
		data.indices.push_back(i == segments - 1 ? 2 : 2 + (i + 1) * 4);


		// top face
		data.indices.push_back(1);
		data.indices.push_back(i == segments - 1 ? 4 : (i + 2) * 4);
		data.indices.push_back((i + 1) * 4);


		// side faces
		data.indices.push_back(3 + i * 4);
		data.indices.push_back(i == segments - 1 ? 5 : 5 + (i + 1) * 4);
		data.indices.push_back(i == segments - 1 ? 3 : 3 + (i + 1) * 4);

		data.indices.push_back(i == segments - 1 ? 5 : 5 + (i + 1) * 4);
		data.indices.push_back(3 + i * 4);
		data.indices.push_back(5 + i * 4);



		//UV calculations

		glm::vec3 normal = glm::normalize(circlePos - glm::vec3(0, -height / 2.0f, 0));

		//top/bottom ring

		float u = (normal.x + 1) / 2;
		float v = (normal.z + 1) / 2;

		//side
		float u2 = (float)i / segments;


		//UV initializations

		//bottom 
		data.uv.push_back(glm::vec2(u, v));
		data.uv.push_back(glm::vec2(u2, 0));

		//top
		data.uv.push_back(glm::vec2(u, v));
		data.uv.push_back(glm::vec2(u2, 1));

	}

	return std::move(data);

}

geometryData geometry::createSphereGeometry(unsigned int longitudeSegments, unsigned int latitudeSegments, float radius)
{
	geometryData data;

	data.positions.push_back(glm::vec3(0.0f, radius, 0.0f));
	data.positions.push_back(glm::vec3(0.0f, -radius, 0.0f));

	data.normals.push_back(glm::vec3(0.0f, radius, 0.0f));
	data.normals.push_back(glm::vec3(0.0f, -radius, 0.0f));

	//UV poles
	data.uv.push_back(glm::vec2(1, 1));
	data.uv.push_back(glm::vec2(1, 0));


	// first and last ring
	for (unsigned int j = 0; j < longitudeSegments; j++) {

		data.indices.push_back(0);
		data.indices.push_back(j == longitudeSegments - 1 ? 2 : (j + 3));
		data.indices.push_back(2 + j);

		data.indices.push_back(2 + (latitudeSegments - 2)*longitudeSegments + j);
		data.indices.push_back(j == longitudeSegments - 1 ? 2 + (latitudeSegments - 2)*longitudeSegments : 2 + (latitudeSegments - 2)*longitudeSegments + j + 1);
		data.indices.push_back(1);

	}


	// vertices and rings
	for (unsigned int i = 1; i < latitudeSegments; i++) {
		float verticalAngle = float(i) * glm::pi<float>() / float(latitudeSegments);
		for (unsigned int j = 0; j < longitudeSegments; j++) {
			float horizontalAngle = float(j) * 2.0f * glm::pi<float>() / float(longitudeSegments);
			glm::vec3 position = glm::vec3(
				radius * glm::sin(verticalAngle) * glm::cos(horizontalAngle),
				radius * glm::cos(verticalAngle),
				radius * glm::sin(verticalAngle) * glm::sin(horizontalAngle)
			);
			data.positions.push_back(position);
			data.normals.push_back(glm::normalize(position));


			// UV
			float u = (float)(j) / longitudeSegments;
			float v = (float)(i) / latitudeSegments;

			data.uv.push_back(glm::vec2(u, v));


			if (i == 1) continue;

			data.indices.push_back(2 + (i - 1)*longitudeSegments + j);
			data.indices.push_back(j == longitudeSegments - 1 ? 2 + (i - 2)*longitudeSegments : 2 + (i - 2)*longitudeSegments + j + 1);
			data.indices.push_back(j == longitudeSegments - 1 ? 2 + (i - 1)*longitudeSegments : 2 + (i - 1)*longitudeSegments + j + 1);

			data.indices.push_back(j == longitudeSegments - 1 ? 2 + (i - 2)*longitudeSegments : 2 + (i - 2)*longitudeSegments + j + 1);
			data.indices.push_back(2 + (i - 1)*longitudeSegments + j);
			data.indices.push_back(2 + (i - 2)*longitudeSegments + j);

		}

	}

	return std::move(data);
}

