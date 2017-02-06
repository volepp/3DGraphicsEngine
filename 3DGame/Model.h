#pragma once

class Model
{
public:
	Model(char *modelFilepath, char *textureFilepath);
	~Model();
	
	void loadOBJ(char* path);
	void loadTexture(char *path);

	void reshape(int w, int h);

	void drawModel();

private:
	std::vector<GLfloat> vertexBufferData, uvBufferData, normalBufferData;
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;

	GLuint textureID;

	GLuint vertexbuffer, uvbuffer, normalbuffer;

	bool textured;
};

