#include "stdafx.h"
#include "Player.h"


Player::Player(glm::vec3 p_location, Window *win)
{
	window = win;

	location = p_location;
	direction = glm::vec3(0, 0, 0);

	camera = new Camera(win, location);

	input = new Input(win);

	speed = 3;
	sensitivity = 0.1f;

	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
}

Player::~Player()
{
}

void Player::update(float deltaTime, double mouseX, double mouseY) {
	horizontalAngle += sensitivity * deltaTime * float(window->getWidth()/2 - mouseX);
	verticalAngle += sensitivity * deltaTime * float(window->getHeight()/2 - mouseY);

	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	); 

	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	takeInput(deltaTime);

	camera->update(location, direction);
}

void Player::takeInput(float deltatime) {
	if (input->keyPressed(GLFW_KEY_W)) {
		location += direction * deltatime * speed;
	}
	if (input->keyPressed(GLFW_KEY_S)) {
		location -= direction * deltatime * speed;
	}
	if (input->keyPressed(GLFW_KEY_A)) {
		location -= right * deltatime * speed;
	}
	if (input->keyPressed(GLFW_KEY_D)) {
		location += right * deltatime * speed;
	}
}

void Player::renderCamera(GLuint programID, GLuint matrixID) {
	camera->render(programID, matrixID);
}