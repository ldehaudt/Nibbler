#include "Nibbler.hpp"
#include "AEntity.hpp"
#include "Game.hpp"

const char* dlException::what() const throw () {
	return dlerror();
}

void dlerror_wrapper(){
	throw dlException();
}

void dlerror_wrapper_wrapper(){
	try{
		dlerror_wrapper();
	}
	catch(dlException & e){
		std::cout << "ERROR : " << e.what() << std::endl;
		exit(1);
	}
}
