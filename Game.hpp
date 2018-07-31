#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "IDynLib.hpp"
#include "Nibbler.hpp"

class Game : public IDynLib {
		int w;
		int h;
		SDL_Texture* snake;
		SDL_Texture* wall;
		SDL_Texture* food;
		SDL_Texture* tfood;
		SDL_Texture* head;
		SDL_Texture* tail;
		SDL_Texture* angle;
		SDL_Texture* background;
		SDL_Texture* start;
		SDL_Texture* gameover;
		SDL_Texture* scoreText;
		SDL_Texture* numbers;
		Game();
		Game(Game const & src);
		Game & operator=(Game & src);
		SDL_Event event;
	public:
		Game(int x, int y);
		~Game();
		SDL_Window *win;
		SDL_Renderer *rend;
		void events(int *input);
		void putScore(int score);
		char getInput();
		void display(char arr[MAX_SIZE + 1][MAX_SIZE + 1]);
		void destroy();
		void gameOver();
		void playTurnSFX();
		void restart();
};

extern "C" {
	IDynLib *startGame(int x, int y);
}

#endif
