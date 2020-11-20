##
## EPITECH PROJECT, 2020
## Games Makefile
## File description:
## Makefile
##

all: $(OBJ)
	make -C ./pacman
	make -C ./Nibbler

clean:
	make clean -C ./pacman
	make clean -C ./Nibbler

fclean: clean
	make fclean -C ./pacman
	make fclean -C ./Nibbler

re: fclean all

.PHONY: all clean fclean re
