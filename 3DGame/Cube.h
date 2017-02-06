#pragma once
#include "Object.h"
#include "Model.h"

class Cube : public Object
{
public:
	Cube(glm::vec3 location);
	~Cube();

private:
	Model *model;
};

