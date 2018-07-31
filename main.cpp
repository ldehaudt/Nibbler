#include "Nibbler.hpp"
#include "AEntity.hpp"
#include "Game.hpp"
#include <map>

std::list<AEntity*>	objects;
pt					mapSize;
bool				multiPlayer;
bool				randomWalls;
bool				speedUp;
float				t;
char				paused;
int					score;
char				arr[MAX_SIZE + 1][MAX_SIZE + 1];
IDynLib				*game;
IDynLib				*(*starter)(int, int);

bool    isEmpty(int x, int y)
{
	std::list<AEntity*>::iterator iter;
	for (iter = objects.begin(); iter != objects.end(); iter++)
		if ((*iter)->getPos().x == x && (*iter)->getPos().y == y)
			return false;
	return true;
}

int main(int ac, char **av)
{
	parse_input(ac, av);
	paused = 1;
	void *dl_handle;
	dl_handle = dlopen("game1.so", RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle)
		dlerror_wrapper_wrapper();
	starter = (IDynLib *(*)(int, int))dlsym(dl_handle, "startGame");
	if (!starter)
		dlerror_wrapper_wrapper();
	game = starter(mapSize.x, mapSize.y);
	sleep(1);
	srand(time(NULL));
	setup();
	int key;
	while ((key = game->getInput()) != esc)
	{
		handle_check(key, &dl_handle);
		if (pauseCheck(key))
		{
			if (!paused)
				game->display(arr);
			game->putScore(score);
			if (speedUp == false)
				usleep(200000);
			else
				usleep(10000 + 190000 * (1 - (score / (mapSize.x * mapSize.y))));
		}
	}
	game->destroy();
	if (dlclose(dl_handle) != 0)
		dlerror_wrapper_wrapper();
}
