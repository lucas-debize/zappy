##
## EPITECH PROJECT, 2024
## Server Zappy
## File description:
## Makefile
##

SRC = $(shell find ./src -name "*.c")
OBJET = $(SRC:.c=.o)
NAME = zappy_server
CC = gcc
CFLAGS = -I./include -Wall -Wextra
LDFLAGS = -lm
CRITERION_FLAGS = -lcriterion --coverage

ifneq ($(shell uname -s), 'Darwin')
	CRITERION_FLAGS += -I/opt/homebrew/include -L/opt/homebrew/lib
endif

$(NAME): $(OBJET)
	$(CC) $(OBJET) $(LDFLAGS) $(CFLAGS) -o $(NAME)
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
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=med --track-origins=yes --vgdb=no ./$(NAME) $(ARGS)

.SILENT: $(OBJ)
.PHONY: all clean fclean re run tests_run tests_clean unit_tests valgrind g3
