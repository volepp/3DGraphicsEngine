#pragma once
#include "Object.h"
#include "Light.h"

class Map
{
public:
	Map();
	~Map();

	/*void update();

	void addObject(Object o) { objects.push_back(o); }
	void addLight(Light l) { lights.push_back(l); }

	std::vector<Object*> getObjects() { return objects; }
	std::vector<Light*> getLights() { return lights; }*/

private:
	std::vector<Object*> objects;
	std::vector<Light*> lights;
};

