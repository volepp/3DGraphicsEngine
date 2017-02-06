#pragma once
#include "stdafx.h"
#include "Window.h"

class Input
{
public:
	Input(Window *window);
	~Input();

	void update();

	bool keyPressed(int key);

	double getMouseX() { return mouseX; }
	double getMouseY() { return mouseY; }

private:
	Window *window;

	double mouseX, mouseY;
};

