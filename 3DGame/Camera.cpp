#include "stdafx.h"
#include "Camera.h"
#include "Model.h"

Camera::Camera(Window *win, glm::vec3 p_location)
{
	window = win;

	location = p_location;
	direction = glm::vec3(0, 0, 0);

	glEnable(GL_CULL_FACE);

	model = new Model("Models/sphere2.obj", "Textures/default.bmp");
}


Camera::~Camera()
{
}

void Camera::setLocation(glm::vec3 loc) {
	location = loc;
}

void Camera::setDirection(glm::vec3 dir) {
	direction = dir;
}

void Camera::update(glm::vec3 p_location, glm::vec3 p_direction) {
	location = p_location;
	direction = p_direction;
}

void Camera::render(GLuint programID, GLuint matrixID) {
	glUseProgram(programID);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model->drawModel();

	glm::mat4 projection = glm::perspective(
		glm::radians(fov), 
		(float)window->getWidth() / (float)window->getHeight(), 
		0.1f, 
		100.0f
		);

	glm::mat4 view = glm::lookAt(
		location,
		location+direction,
		glm::vec3(0, 1, 0)
		);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 mvp = projection * view * model;

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
}