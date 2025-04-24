#include "MainGame.h"

void MainGame::init()
{
	SDL_Init(SDL_INIT_HAPTIC | SDL_INIT_CAMERA | SDL_INIT_EVENTS);
	window = SDL_CreateWindow("TrALAlero TraLAla", width, height, SDL_WINDOW_OPENGL);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //TRABAJA CON 2 PANTALLA PARA QUE NO SE VEA EL RENDERIZADO CONTINUO
	glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
	initShaders();

}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_EVENT_MOUSE_MOTION:
			cout << "posicion x " << event.motion.x << " posicion y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	width = 800;
	height = 800;
	gameState = GameState::PLAY;
	init();
	sprite.init(-1, -1, 1, 1);
	update();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}

// Que hace el or binario ( | )
// GL_COLOR_BUFFER_BIT = 0x00004000
// GL_DEPTH_BUFFER_BIT = 0x00000100
// GL_DEPTH_BUFFER_BIT = 0x00004100

void MainGame::draw()
{
	glClearDepth(1.0); //RESETEA LA POSICION DE LA CAMARA
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //BORRA EL FONDO Y VUELVE A FORZAR EL RESETEO DE LA CAMARA
	sprite.draw();
	SDL_GL_SwapWindow(window); //INTERCAMBIA LAS PANTALLAS PARA QUE SE VEA FLUIDO
}
