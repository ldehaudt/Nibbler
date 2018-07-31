#include "Nibbler.hpp"
#include "AEntity.hpp"
#include "Game.hpp"

char	angle[4][4];

void print_usage(){
	std::cout << "usage: nibbler [-[m][w][t]] [width height]\n"
	<< "\t" << MIN_SIZE << " <= width <= " << MAX_SIZE << " & "
	<< MIN_SIZE << " <= height <= " << MAX_SIZE << std::endl
	<< "\t-m multiple players\n" << "\t-w obstacles\n" << "\t-t speed up over time\n";
	exit (1);
}

void init_angle()
{
	angle[0][1] = 'C';
	angle[0][3] = 'D';
	angle[1][0] = 'A';
	angle[1][2] = 'D';
	angle[2][1] = 'B';
	angle[2][3] = 'A';
	angle[3][0] = 'B';
	angle[3][2] = 'C';
}

void parse_input(int ac, char **av){
	int i = 1;
	mapSize.x = 20;
	mapSize.y = 20;
	if (ac == 1)
		return ;
	if (ac > 4)
		print_usage();
	if (av[i][0] == '-')
	{
		std::string flags = av[1];
		if (flags.find('m') != std::string::npos)
			multiPlayer = 1;
		if (flags.find('t') != std::string::npos)
			speedUp = 1;		
		if (flags.find('w') != std::string::npos)
			randomWalls = 1;
		i++;
	}
	if ((av[i] && !av[i + 1]) || (av[i] && av[i + 1] && av[i + 2]))
		print_usage();
	if (av[i])
	{
		try {
			mapSize.x = std::stoi(av[i]);
			mapSize.y = std::stoi(av[i + 1]);
		}
		catch (std::exception &)
		{
			print_usage();
		}
		if (mapSize.x < 10 || mapSize.x > 40 || mapSize.y < 10 || mapSize.y > 40)
			print_usage();
	}
}

void setup(){
	for (int i = 0; i < MAX_SIZE + 1; i++)
		for (int j = 0; j < MAX_SIZE + 1; j++)
			arr[j][i] = 0;
	for (int i = 0; i < mapSize.y; i++){
		for (int j = 0; j < mapSize.x; j++){
			if (i == 0 || j == 0 || i == mapSize.y - 1 || j == mapSize.x - 1){
				objects.push_back(new Wall(j, i));
			}
		}
	}
	objects.push_back(new SnakeHead(mapSize.x / 2, mapSize.y / 2,
		right, kUp, kRight, kDown, kLeft));
	if (multiPlayer)
		objects.push_back(new SnakeHead(mapSize.x / 2, mapSize.y / 2 + 1, left, w, d, s, a));
	Food::generateFood();
	for (int i = 0; i < 10 && randomWalls == true; i++)
		Wall::generateWall();
	init_angle();
}
