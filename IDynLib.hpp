#ifndef I_DYN_LIB_HPP
#define I_DYN_LIB_HPP

#include <vector>
#include "Nibbler.hpp"

class IDynLib {

	public:
		virtual char getInput() = 0;
		virtual void display(char arr[MAX_SIZE + 1][MAX_SIZE + 1]) = 0;
		virtual void destroy() = 0;
		virtual void gameOver() = 0;
		virtual void putScore(int score) = 0;
		virtual void restart() = 0;
};

#endif
