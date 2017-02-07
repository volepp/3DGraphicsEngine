#pragma once
#include "stdafx.h"
#include "Window.h"
#include "Input.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	void init();

	GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);

	void run();

	void draw();
	void update(float deltatime);

	Window* getWindow() { return window; }

private:
	Window *window;

	bool running;

	Input *input;

	GLuint vertexbuffer, programID, matrixID;

	Player *player;
};

