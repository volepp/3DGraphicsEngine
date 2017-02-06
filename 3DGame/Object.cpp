#include "stdafx.h"
#include "Object.h"


Object::Object(glm::vec3 p_location)
{
	location = p_location;
}


Object::~Object()
{
}

void Object::render() {
	if (model != nullptr) {
		model->drawModel();
	}
}

void Object::update() {

}