#pragma once
#include "Model.h"

class Object
{
public:
	Object(glm::vec3 location);
	~Object();

	virtual void update();
	virtual void render();

	glm::vec3 getLocation() { return location; }

private:
	glm::vec3 location;

	Model *model;
};

