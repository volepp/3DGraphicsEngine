#include "stdafx.h"
#include "Model.h"


Model::Model(char *modelFilepath, char *textureFilepath) {
	loadTexture(textureFilepath);

	loadOBJ(modelFilepath);
}


Model::~Model()
{
}

void Model::loadOBJ(char *filepath) {
	std::cout << "Loading " << filepath << std::endl;

	FILE *fp;
	int read;
	GLfloat x, y, z;
	fp = fopen(filepath, "r");

	vertexBufferData.clear();

	if (fp == nullptr) {
		perror("Error");
		return;
	}

	glPointSize(1.0f);

	while (1) {
		char lineHeader[128];

		read = fscanf(fp, "%s", lineHeader);
		if (read == EOF) {
			break; // EOF = End Of File
		}
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%f %f %f\n", &x, &y, &z);

			vertices.push_back(glm::vec3(x, y, z));
		} 
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(fp, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			int vertexIndices[3], uvIndices[3], normalIndices[3];

			fscanf(fp, "%i/%i/%i %i/%i/%i %i/%i/%i\n", &vertexIndices[0], &uvIndices[0], &normalIndices[0], &vertexIndices[1], &uvIndices[1], &normalIndices[1], &vertexIndices[2], &uvIndices[2], &normalIndices[2]);

			vertexBufferData.push_back(vertices[vertexIndices[0] - 1].x);
 			vertexBufferData.push_back(vertices[vertexIndices[0] - 1].y);
			vertexBufferData.push_back(vertices[vertexIndices[0] - 1].z);
			vertexBufferData.push_back(vertices[vertexIndices[1] - 1].x);
			vertexBufferData.push_back(vertices[vertexIndices[1] - 1].y);
			vertexBufferData.push_back(vertices[vertexIndices[1] - 1].z);
			vertexBufferData.push_back(vertices[vertexIndices[2] - 1].x);
			vertexBufferData.push_back(vertices[vertexIndices[2] - 1].y);
			vertexBufferData.push_back(vertices[vertexIndices[2] - 1].z);

			uvBufferData.push_back(uvs[uvIndices[0] - 1].x);
			uvBufferData.push_back(uvs[uvIndices[0] - 1].y);
			uvBufferData.push_back(uvs[uvIndices[1] - 1].x);
			uvBufferData.push_back(uvs[uvIndices[1] - 1].y);
			uvBufferData.push_back(uvs[uvIndices[2] - 1].x);
			uvBufferData.push_back(uvs[uvIndices[2] - 1].y);

			normalBufferData.push_back(normals[normalIndices[0] - 1].x);
			normalBufferData.push_back(normals[normalIndices[0] - 1].y);
			normalBufferData.push_back(normals[normalIndices[0] - 1].z);
			normalBufferData.push_back(normals[normalIndices[1] - 1].x);
			normalBufferData.push_back(normals[normalIndices[1] - 1].y);
			normalBufferData.push_back(normals[normalIndices[1] - 1].z);
			normalBufferData.push_back(normals[normalIndices[2] - 1].x);
			normalBufferData.push_back(normals[normalIndices[2] - 1].y);
			normalBufferData.push_back(normals[normalIndices[2] - 1].z);
		}
	}

	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof(GLfloat), &vertexBufferData[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvBufferData.size() * sizeof(GLfloat), &uvBufferData[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normalBufferData.size() * sizeof(GLfloat), &normalBufferData[0], GL_STATIC_DRAW);

	fclose(fp);

	std::cout << "Done\n";
}

void Model::loadTexture(char *path) {
	int width, height;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Model::reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Model::drawModel() {
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,			
		3,			
		GL_FLOAT,	
		GL_FALSE,	
		0,			
		(void*)0	
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, vertexBufferData.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}