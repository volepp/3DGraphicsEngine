#pragma once
#include "Window.h"
#include "Map.h"

class Camera
{
public:
	Camera(Window *win, Map *map, glm::vec3 p_location);
	~Camera();

	void setLocation(glm::vec3 loc);
	void setDirection(glm::vec3 direction);
	void setFov(float newFov) { fov = newFov; }

	void update(glm::vec3 location, glm::vec3 direction);
	void render(GLuint programID, GLuint matrixID);

private:
	Window *window;

	Map *map;

	glm::vec3 location;
	glm::vec3 direction;

	float fov = 45.0f;

	Model *model;
};

