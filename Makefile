NAME = nibbler

SRC = main.cpp AEntity.cpp start.cpp dlManager.cpp iterate.cpp

FRAMEWORKS = -framework OpenGl

BREW_INC = -I ~/.brew/include

SDL_LINK = -g  -L ~/.brew/lib -l SDL2

FLAGS = -Wfatal-errors -O3 -lcurses

all: $(NAME)

$(NAME):	
ifneq ("$(shell test -e $(HOME)/.brew && echo ex)" , "ex")
	@echo "BREW INSTALLING ..."
	@mkdir $(HOME)/.brew && curl -fsSL https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C $(HOME)/.brew
	@mkdir -p /tmp/.$(whoami)-brew-locks
	@mkdir -p $(HOME)/.brew/var/homebrew
	@ln -s /tmp/.$(whoami)-brew-locks $(HOME)/.brew/var/homebrew/locks
	@export PATH="$(HOME)/.brew/bin:$(PATH)"
	@brew update && brew upgrade
	@echo "INSTALLING SDL2: please be patient"
endif
	@echo "Checking for graphics library ..."	
	@ brew install sdl2
	g++ -std=c++11 -shared -fPIC -O3 -framework OpenGl -I ~/.brew/include -g -L ~/.brew/lib -l SDL2 -o game1.so GameV1.cpp
	g++ -std=c++11 -shared -fPIC -O3 -framework OpenGl -I ~/.brew/include -g -L ~/.brew/lib -l SDL2 -o game2.so GameV2.cpp
	g++ -std=c++11 -shared -fPIC -O3 -framework OpenGl -I ~/.brew/include -g -L ~/.brew/lib -l SDL2 -o game3.so GameV3.cpp
	g++ -std=c++11 -g $(FLAGS) $(SRC) -o $(NAME) $(FRAMEWORKS) $(BREW_INC) $(SDL_LINK)

clean:
	rm -f *.o
	rm -rf game*.so.*
	rm -rf nibbler.dSYM

fclean: clean
	rm -f $(NAME)
	rm -rf game*.so

re: fclean all
