#pragma once
#include <SDL3/SDL.h>
#include <GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLSProgram.h"

using namespace std;

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	int width;
	int height;
	Sprite sprite;
	GLSProgram program;
	SDL_Window* window;
	
	void init();
	void processInput();
	void initShaders();

public:
	MainGame();
	~MainGame();
	GameState gameState;

	void run();
	void update();
	void draw();
};

