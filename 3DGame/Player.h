#pragma once
#include "Camera.h"
#include "Input.h"

class Player
{
public:
	Player(glm::vec3 location, Window *win);
	~Player();

	void update(float deltatime, double mouseX, double mouseY);

	void renderCamera(GLuint programID, GLuint matrixID);

	void takeInput(float deltatime);

private:
	Window *window;

	Camera *camera;

	Input *input;

	glm::vec3 location;
	glm::vec3 direction;
	glm::vec3 right, up;

	float speed, sensitivity;
	float horizontalAngle, verticalAngle;
};

