##
## EPITECH PROJECT, 2023
## Untitled (Workspace)
## File description:
## Makefile
##

all: server gui ai

gui:
	@$(MAKE) -C gui/ -s
	@cp gui/zappy_gui .

server:
	@$(MAKE) -C server/ -s
	@cp server/zappy_server .

ai:
	@$(MAKE) -C ai/ -s
	@#cp ai/zappy_ai

clean:
	@$(MAKE) -C server/ clean -s
	@$(MAKE) -C gui/ clean -s
	@$(MAKE) -C ai/ clean -s

fclean:
	@$(MAKE) -C server/ fclean -s
	@rm -f zappy_server
	@$(MAKE) -C gui/ fclean -s
	@rm -f zappy_gui
	@$(MAKE) -C ai/ fclean -s

re: fclean all

.SILENT: all server gui ai clean fclean re
.PHONY: all server gui ai clean fclean re
