#include "stdafx.h"
#include "Camera.h"
#include "Model.h"

Camera::Camera(Window *win, Map *p_map, glm::vec3 p_location)
{
	window = win;

	map = p_map;

	location = p_location;
	direction = glm::vec3(0, 0, 0);

	glEnable(GL_CULL_FACE);

	model = new Model("Models/texturedcube.obj", "Textures/smiley.bmp");
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

	/*std::vector<Object*> objects = map->getObjects();

	for (int i = 0; i < objects.size(); i++) {
		Object *o = objects.at(i);
		o->render();
	}*/

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