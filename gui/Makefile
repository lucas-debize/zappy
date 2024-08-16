##
## EPITECH PROJECT, 2024
## ThePlazza
## File description:
## Makefile
##

SRC = $(shell find ./src -name "*.cpp")
OBJET = $(SRC:%.cpp=%.o)
NAME = zappy_gui
CC = g++
CFLAGS = -Wall -Wextra -Werror
CXXFLAGS = -Iinclude -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system \
			-lsfml-audio -lsfml-network
LEAKS = -fsanitize=address
CRITERION_FLAGS = -lcriterion --coverage

ifneq ($(shell uname -s), 'Darwin')
	CRITERION_FLAGS += -I/opt/homebrew/include
	LDFLAGS += -L/opt/homebrew/lib -L/opt/homebrew/Cellar/sfml/2.6.1/lib
	CXXFLAGS += -I/opt/homebrew/Cellar/sfml/2.6.1/include/
endif

$(NAME): $(OBJET)
	$(CC) $(OBJET) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "\033[32m==========Compilation done for $(NAME)==========\033[0m"

all: $(NAME)

clean:
	rm -f $(OBJET)
	@echo "\033[33m======Clean all files *.o of $(NAME) done======\033[0m"

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests
	@echo "\033[33m=========Clean the binary $(NAME) done=========\033[0m"

re: fclean all

run: all
	@./$(NAME) $(ARGS)

g3: fclean
	$(CC) $(SRC) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $(NAME) -g3
	@echo "\033[32m==========Compilation done for $(NAME) g3==========\033[0m"

valgrind: g3
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=med \
	--track-origins=yes --vgdb=no ./$(NAME) $(ARGS)

.SILENT: $(OBJ)
.PHONY: all clean fclean re run valgrind g3
