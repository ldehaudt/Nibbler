#ifndef A_ENTITY
#define A_ENTITY

#include "Nibbler.hpp"

class AEntity{
private:
	AEntity(AEntity const & src);
	AEntity & operator=(AEntity const & src);

protected:
	pt pos;
	entityType type;
	direction dir;

public:
	AEntity();
	AEntity(int xPos , int yPos, entityType t);
	virtual ~AEntity();
	virtual gameStatus update() = 0;
	pt getPos();
	direction getDir();
	entityType getType();
};

class SnakeHead: public AEntity{

private:
	direction input;

public:
	keys      ks;
	int length;
	SnakeHead();
	SnakeHead(int xPos, int yPos, direction dir, int up, int right, int down, int left);
	SnakeHead(SnakeHead const & src);
	SnakeHead & operator=(SnakeHead const & src);
	~SnakeHead();
	void setInput(direction dir);
	gameStatus      update();
	gameStatus      checkColisions();
};

class SnakeBody: public AEntity{

private:
	int     t;
	SnakeHead*  head;
	direction pDir;

public:
	SnakeBody();
	SnakeBody(int xPos, int yPos, direction mvDir, direction prevDir, SnakeHead *h);
	SnakeBody(direction dir);
	SnakeBody(SnakeBody const & src);
	SnakeBody & operator=(SnakeBody const & src);
	~SnakeBody();
	direction getPDir();
	int getT();
	SnakeHead* getHead();
	gameStatus    update();
};

class Food: public AEntity{
private:
	Food(Food &);
	Food & operator=(Food &);

public:
	Food();
	virtual ~Food();
	virtual gameStatus    update();
	Food(int xPos, int yPos);
	Food(int xPos, int yPos, entityType t);
	static void generateFood();
};

class TimedFood: public Food{
private:
	int t;
	TimedFood();
	TimedFood(TimedFood &);
	TimedFood & operator=(TimedFood &);

public:
	~TimedFood();
	gameStatus    update();
	TimedFood(int xPos, int yPos);
	static void generateFood();
};

class Wall: public AEntity{
public:
	gameStatus    update();
	Wall(int xPos, int yPos);
	static void generateWall();
};

#endif
