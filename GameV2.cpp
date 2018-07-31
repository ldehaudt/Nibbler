#include "Game.hpp"
#include "Nibbler.hpp"
#include <map>

std::map<SDL_Keycode,inKeys> inputs = {
	{SDLK_UP,kUp},
	{SDLK_RIGHT,kRight},
	{SDLK_DOWN,kDown},
	{SDLK_LEFT,kLeft},
	{SDLK_w,w},
	{SDLK_a,a},
	{SDLK_s,s},
	{SDLK_d,d},
	{SDLK_1,k1},
	{SDLK_2,k2},
	{SDLK_3,k3},
	{SDLK_ESCAPE,esc},
	{SDLK_SPACE,space},
};

Game::Game(Game const & src) {}
Game & Game::operator=(Game & src) {return src;}
Game::Game() {}

Game::Game(int x, int y) : w(x), h(y){
	SDL_Surface *tmpSurf;

	SDL_Init(SDL_INIT_VIDEO);
	win= SDL_CreateWindow
	("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	50 * (x + 2), 50 * (y + 3), SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(win, -1, 0);
	SDL_SetRenderDrawColor(rend, 9, 71, 124, 255);
	tmpSurf = SDL_LoadBMP("hexel/hexelSnakeStr.bmp");
	snake = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelApple.bmp");
	food = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelBanana.bmp");
	tfood = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelWall.bmp");
	wall = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelSnakeHead.bmp");
	head = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelSnakeButt.bmp");
	tail = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelSnakeAngle.bmp");
	angle = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelBackground.bmp");
	background = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelGameover.bmp");
	gameover = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelStart.bmp");
	start = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelScore.bmp");
	scoreText = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	tmpSurf = SDL_LoadBMP("hexel/hexelNumbers.bmp");
	numbers = SDL_CreateTextureFromSurface(rend, tmpSurf);
	SDL_FreeSurface(tmpSurf);
	SDL_RenderFillRect(rend, NULL);
	SDL_RenderCopy(rend, start, NULL, NULL);
	SDL_RenderPresent(rend);
}

void Game::restart(){
	SDL_RenderClear(rend);
	SDL_RenderFillRect(rend, NULL);
	SDL_RenderCopy(rend, start, NULL, NULL);
	SDL_RenderPresent(rend);
}

Game::~Game() {
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
}

void Game::destroy(){
	delete this;
}

void Game::gameOver(){
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, gameover, NULL, NULL);
	SDL_RenderPresent(rend);
}

char Game::getInput()
{
	while (SDL_PollEvent(&event) != 0 && (event.type == SDL_KEYUP
		|| event.type == SDL_MOUSEMOTION || event.key.repeat != 0))
		;
	switch (event.type) {
		case SDL_QUIT:
			return esc;
		case SDL_KEYDOWN:
			if (inputs.find(event.key.keysym.sym) != inputs.end())
			return inputs[event.key.keysym.sym];
		default:
			return -1;
	}
}

void Game::display(char arr[MAX_SIZE + 1][MAX_SIZE + 1]) {
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, background, NULL, NULL);
	SDL_Rect rect;
	rect.w = 50;
	rect.h = 50;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (arr[i][j] == 0)
				continue;
			rect.x = j * 50 + 50;
			rect.y = i * 50 + 100;
			if (arr[i][j] == 'w')
				SDL_RenderCopy(rend, wall, NULL, &rect);
			if (arr[i][j] >= 'a' && arr[i][j] <= 'd')
				SDL_RenderCopyEx(rend, head, NULL, &rect,
					90 * (arr[i][j] - 'b'), NULL, SDL_FLIP_NONE);
			else if (arr[i][j] == 'f')
				SDL_RenderCopy(rend, food, NULL, &rect);
			else if (arr[i][j] == 't')
				SDL_RenderCopy(rend, tfood, NULL, &rect);
			else if (arr[i][j] >= '0' && arr[i][j] <= '3')
				SDL_RenderCopyEx(rend, snake, NULL, &rect,
					90 * (arr[i][j] - '1'), NULL, SDL_FLIP_NONE);
			else if (arr[i][j] >= '4' && arr[i][j] <= '7')
				SDL_RenderCopyEx(rend, tail, NULL, &rect,
					90 * (arr[i][j] - '1'), NULL, SDL_FLIP_NONE);
			else if (arr[i][j] >= 'A' && arr[i][j] <= 'D')
				SDL_RenderCopyEx(rend, angle, NULL, &rect,
					90 * (arr[i][j] - 'A'), NULL, SDL_FLIP_NONE);
		}
	}
}

void Game::putScore(int score){
	SDL_Rect rect = {50, 30, 200, 50};
	SDL_RenderCopy(rend, scoreText, NULL, &rect);
	SDL_Rect num = {0, 0, 50, 50};
	int cent = score / 100;
	int dix = (score / 10) % 10;
	int un = (score % 100) % 10;
	rect.x = 300;
	rect.w = 50;
	num.x = 50 * cent;
	SDL_RenderCopy(rend, numbers, &num, &rect);
	rect.x = 355;
	num.x = 50 * dix;
	SDL_RenderCopy(rend, numbers, &num, &rect);
	rect.x = 410;
	num.x = 50 * un;
	SDL_RenderCopy(rend, numbers, &num, &rect);
	SDL_RenderPresent(rend);
}

IDynLib *startGame(int x, int y) {
	return new Game(x, y);
}
