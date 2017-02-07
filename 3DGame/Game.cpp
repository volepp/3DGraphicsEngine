#include "stdafx.h"
#include "Game.h"
#include "Camera.h"

Game::Game()
{
	init();
}


Game::~Game()
{
}

void Game::init() {
	window = new Window(1280, 768, "Game");
	glfwSetWindowPos(window->getWindow(), 1000, 200);

	input = new Input(window);

	player = new Player(glm::vec3 (0, 0, 5), window);

	

	programID = loadShaders("Shaders/vertexshader.txt", "Shaders/fragmentshader.txt");
}

GLuint Game::loadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line)) {
			VertexShaderCode += "\n" + Line;
		}
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line)) {
			FragmentShaderCode += "\n" + Line;
		}
		FragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile vertex shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, infoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, infoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &result);
	if (infoLogLength > 0) {
		std::vector<char> ProgramShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(ProgramID, infoLogLength, nullptr, &ProgramShaderErrorMessage[0]);
		printf("%s\n", &ProgramShaderErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	printf("Done!\n");
		
	return ProgramID;
}

void Game::run() {
	running = true;

	float currentTime = glfwGetTime();
	float lastTime = currentTime;
	float deltaTime = float(currentTime - lastTime);

	while (running) {
		if (input->keyPressed(GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window->getWindow())) {
			break;
		}
		
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		update(deltaTime);
		draw();	
	}
}

void Game::draw() {

	player->renderCamera(programID, matrixID);
}

void Game::update(float deltatime) {
	matrixID = glGetUniformLocation(programID, "MVP");

	window->update();
	input->update();

	double mouseX, mouseY;

	player->update(deltatime, input->getMouseX(), input->getMouseY());
}
