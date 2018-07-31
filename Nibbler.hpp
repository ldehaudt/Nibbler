#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include <list>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include <dlfcn.h>

#define MAX_SIZE 40
#define MIN_SIZE 10

class	AEntity;
class	IDynLib;

enum	entityType {head, body, wall, food, timeFood};
enum	gameStatus {normal, pieceDead, gameOver};
enum	direction {up, right, down, left};
enum	inKeys{kUp, kRight, kDown, kLeft, w, a, s, d, k1, k2, k3, esc, space};

typedef struct s_pt{
    int		x;
    int		y;
}               pt;

typedef struct	s_keys{
    int			u;
    int			r;
    int			d;
    int			l;
}				keys;

extern std::list<AEntity*>	objects;
extern pt					mapSize;
extern bool					multiPlayer;
extern bool					randomWalls;
extern bool					speedUp;
extern float				t;
extern char					paused;
extern int					score;
extern char					arr[MAX_SIZE + 1][MAX_SIZE + 1];
extern char					angle[4][4];
extern IDynLib				*game;
extern IDynLib				*(*starter)(int, int);

void	parse_input(int ac, char **av);
void	setup();
void	dlerror_wrapper_wrapper();
void	iterate_object(std::list<AEntity*>::iterator iter, int key);
void	handle_check(int key, void **dl_handle);
bool	pauseCheck(int key);

class	dlException : public std::exception {
    public:
		virtual const char* what() const throw();
};

#endif