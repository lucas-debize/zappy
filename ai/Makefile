## EPITECH PROJECT, 2023
## B-YEP-400-LYN-4-1-zappy-bryan.bole
## File description:
## Makefile

SRC_DIR := src
NAME := zappy_ai
PYTHON := python3
MAIN := $(SRC_DIR)/main.py

debug: CXXFLAGS += -g -D DEBUG

all: ../$(NAME)

debug: ../$(NAME)

release: fclean ../$(NAME)

../$(NAME):
	@echo "Creating binary."
	@echo "#!/usr/bin/env python3" >> ../$(NAME)
	@cat $(MAIN) >> ../$(NAME)
	@chmod +x ../$(NAME)


clean:
	@echo "Nothing to do for clean rule."

fclean: clean
	@rm -f ../$(NAME)
	@rm -f $(NAME)
	@echo "Removing binary file."

re: fclean all