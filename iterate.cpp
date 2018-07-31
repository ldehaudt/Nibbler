#include "Nibbler.hpp"
#include "AEntity.hpp"
#include "Game.hpp"
#include <map>

std::map<entityType , char> charMap = {
	{wall, 'w'},
	{food, 'f'},
	{timeFood, 't'},
};

void handle_check(int key, void **dl_handle)
{
	if (key == k1 || key == k2 || key == k3)
	{
		game->destroy();
		if (dlclose(*dl_handle) != 0)
			dlerror_wrapper_wrapper();
		switch (key) {
			case k1 : *dl_handle = dlopen("game1.so", RTLD_LAZY | RTLD_LOCAL);
				break ;
			case k2 : *dl_handle = dlopen("game2.so", RTLD_LAZY | RTLD_LOCAL);
				break ;
			case k3 : *dl_handle = dlopen("game3.so", RTLD_LAZY | RTLD_LOCAL);
				break ;
		}
		if (!*dl_handle)
			dlerror_wrapper_wrapper();
		starter = (IDynLib *(*)(int, int))dlsym(*dl_handle, "startGame");
		if (!starter)
			dlerror_wrapper_wrapper();
		game = starter(mapSize.x, mapSize.y);
	}
}

bool pauseCheck(int key)
{
	if (paused) {
		if (paused == 2)
			game->gameOver();
		if (key == space) {
			if (paused == 2) {
				std::list<AEntity*>::iterator iter;
				for (iter = objects.begin(); iter != objects.end(); iter++)
					delete (*iter);
				objects.clear();
				setup();
				game->restart();
			}
			paused--;
		}
		return 0;
	}
	else {
		if ((rand() % 30) == 0)
			TimedFood::generateFood();
		std::list<AEntity*>::iterator iter;
		score = 0;
		for (iter = objects.begin(); iter != objects.end() && !paused; iter++)
			iterate_object(iter, key);
	}
	return 1;
}

void	iterate_object(std::list<AEntity*>::iterator iter, int key){
	if ((*iter)->getType() == head)
	{
		SnakeHead *h = dynamic_cast<SnakeHead*>(*iter);
		if (h->length > score)
			score = h->length;
		if (key == h->ks.u)
				h->setInput(up);
		else if (key == h->ks.d)
				h->setInput(down);
		else if (key == h->ks.r)
				h->setInput(right);
		else if (key == h->ks.l)
				h->setInput(left);
		arr[(*iter)->getPos().y][(*iter)->getPos().x] = 'a' + (*iter)->getDir();
	}
	else if (charMap[(*iter)->getType()])
		arr[(*iter)->getPos().y][(*iter)->getPos().x] = charMap[(*iter)->getType()];
	else
	{
		SnakeBody *tmp = dynamic_cast<SnakeBody*>(*iter); 
		if (tmp->getT() == tmp->getHead()->length - 2){
			arr[(*iter)->getPos().y][(*iter)->getPos().x] = '4' + (*iter)->getDir();
		}
		else if (tmp->getDir() == tmp->getPDir())
			arr[(*iter)->getPos().y][(*iter)->getPos().x] = '0' + (*iter)->getDir();
		else
			arr[(*iter)->getPos().y][(*iter)->getPos().x]
		= angle[tmp->getDir()][tmp->getPDir()];
	}
	gameStatus st = (*iter)->update();
	switch (st)
	{
		case normal:
			break;
		case pieceDead:
			arr[(*iter)->getPos().y][(*iter)->getPos().x] = 0;
			delete *iter;
			iter = objects.erase(iter);
			break;
		case gameOver:
			paused = 2;
			game->gameOver();
			break;
	}
}