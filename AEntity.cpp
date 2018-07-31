#include "AEntity.hpp"
#include "Nibbler.hpp"
#include <iostream>

bool isEmpty(int x, int y);

AEntity::AEntity(){}
AEntity::AEntity(AEntity const & src){}
AEntity & AEntity::operator=(AEntity const & src){return *this;}
AEntity::~AEntity(){}

AEntity::AEntity(int x , int y, entityType t) : type(t){
	pos.x = x;
	pos.y = y;
}

entityType AEntity::getType(){
	return type;
}

pt AEntity::getPos(){
	return pos;
}

direction AEntity::getDir(){
	return dir;
}

SnakeHead::SnakeHead(){}
SnakeHead::SnakeHead(SnakeHead const & src){}
SnakeHead & SnakeHead::operator=(SnakeHead const & src){return *this;}
SnakeHead::~SnakeHead(){}

void    SnakeHead::setInput(direction dir){
	input = dir;
}

gameStatus    SnakeHead::checkColisions(){
	std::list<AEntity*>::iterator iter;
	for (iter = objects.begin(); iter != objects.end(); iter++)
		if (pos.x == (*iter)->getPos().x && pos.y == (*iter)->getPos().y)
		{
			if ((*iter)->getType() == food || (*iter)->getType() == timeFood)
			{
				length++;
				if ((*iter)->getType() == food)
					Food::generateFood();
				delete (*iter);
				iter = objects.erase(iter);                 
			}
			else if ((*iter)->getType() != head)
				return (gameOver);
		}
	return (normal);
}

SnakeHead::SnakeHead(int xPos, int yPos, direction stDir, int u, int r, int d, int l)
: AEntity(xPos, yPos, head), input(stDir), length(4){
	dir = stDir;
	ks.u = u;
	ks.r = r;
	ks.d = d;
	ks.l = l;
}

gameStatus    SnakeHead::update(){
	direction prevDir = dir;
	if (dir != input && ((dir + 2) % 4) != input){
		dir = input;
	}
	gameStatus st = checkColisions();
	objects.push_front(new SnakeBody(pos.x, pos.y, dir, prevDir, this));
	switch (dir){
		case up:
		pos.y--;
		break;
		case down:
		pos.y++;
		break;
		case left: 
		pos.x--;
		break;
		case right: 
		pos.x++;
		break;
	}
	return st;
}

SnakeBody::SnakeBody(){}
SnakeBody::SnakeBody(SnakeBody const & src){}
SnakeBody & SnakeBody::operator=(SnakeBody const & src){return *this;}
SnakeBody::~SnakeBody(){}

SnakeBody::SnakeBody(int xPos, int yPos, direction mvDir, direction prevDir, SnakeHead* h)
: AEntity(xPos, yPos, body), pDir(prevDir), t(0), head(h){
	dir = mvDir;
}

direction SnakeBody::getPDir(){
	return pDir;
}

int SnakeBody::getT(){
	return t;
}

SnakeHead* SnakeBody::getHead(){
	return head;
}

gameStatus    SnakeBody::update(){
	this->t++;    
	if (this->t >= head->length){
		return pieceDead;
	}
	return normal;
}


Food::Food(Food &){}
Food & Food::operator=(Food &){return *this;}
Food::Food(){}
Food::~Food(){}
Food::Food(int xPos, int yPos) : AEntity(xPos, yPos, food){}

Food::Food(int xPos, int yPos, entityType t) : AEntity(xPos, yPos, t){}

void Food::generateFood()
{
	int rX;
	int rY;
	do{
		rX = rand() % static_cast<int>(mapSize.x - 2) + 1;
		rY = rand() % static_cast<int>(mapSize.y - 2) + 1;
	} while(!isEmpty(rX, rY));
	objects.push_back(new Food(rX,rY));
}

gameStatus    Food::update(){return normal;}


TimedFood::TimedFood(){}
TimedFood::TimedFood(TimedFood &){}
TimedFood & TimedFood::operator=(TimedFood &){return *this;}
TimedFood::~TimedFood(){}
gameStatus TimedFood::update(){
	t--;
	if(t == 0)
		return pieceDead;
	return normal;
}
TimedFood::TimedFood(int xPos, int yPos) : Food(xPos, yPos, timeFood), t(30){}
void TimedFood::generateFood(){
	int rX;
	int rY;
	do{
		rX = rand() % static_cast<int>(mapSize.x - 2) + 1;
		rY = rand() % static_cast<int>(mapSize.y - 2) + 1;
	} while(!isEmpty(rX, rY));
	objects.push_back(new TimedFood(rX,rY));
}


Wall::Wall(int xPos, int yPos) : AEntity(xPos, yPos, wall){}

void Wall::generateWall()
{
	int rX;
	int rY;
	do{
		rX = rand() % static_cast<int>(mapSize.x - 2) + 1;
		rY = rand() % static_cast<int>(mapSize.y - 2) + 1;
	} while(!isEmpty(rX, rY) || (rY == mapSize.y / 2 + 1 || rY == mapSize.y / 2));
	objects.push_back(new Wall(rX,rY));
}

gameStatus    Wall::update(){return normal;}
