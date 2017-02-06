#include "stdafx.h"
#include "Input.h"


Input::Input(Window *p_window)
{
	window = p_window;
}


Input::~Input()
{
}

void Input::update() {
	// Ensure we can capture the keys being pressed
	glfwSetInputMode(window->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwGetCursorPos(window->getWindow(), &mouseX, &mouseY);

	glfwSetCursorPos(window->getWindow(), window->getWidth()/2, window->getHeight()/2);
}

bool Input::keyPressed(int key) {
	return glfwGetKey(window->getWindow(), key);
}