#pragma once
class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	void update();

	int getWidth() { return width; }
	int getHeight() { return height; }
	GLFWwindow* getWindow() { return window; }

private:
	GLFWwindow *window;

	int width, height;
	const char* title;

private:
	void init();
};

