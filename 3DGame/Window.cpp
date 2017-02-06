#include "stdafx.h"
#include "Window.h"


Window::Window(int p_width, int p_height, const char* p_title)
{
	width = p_width;
	height = p_height;
	title = p_title;

	init();
}


Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::init() {
	if (!glfwInit()) {
		fprintf(stderr, "Couldn't initialize GLFW!\n");
		return;
	}
	else {
		glfwWindowHint(GLFW_SAMPLES, 4); // Antialiasing 4x
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL version 3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Dismiss old OpenGL

		// Open a window
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr) {
			fprintf(stderr, "Couldn't open a window!\n");
			glfwTerminate();
			return;
		}

		// Initializing GLEW
		glfwMakeContextCurrent(window);
		glewExperimental = true; // Needed in core profile

		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Couldn't initialize GLEW!\n");
			return;
		}
	}
}

void Window::update() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}