##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= 	main.cpp \
			core/srcs/Core.cpp \
			core/srcs/Info.cpp \
			core/srcs/Score.cpp \
			core/srcs/InitTab.cpp \
			core/srcs/Exception.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -W -Wall -Wextra -W -fPIC -rdynamic -g3
CPPFLAGS += -ldl -I./ -I./core -I./lib -I./games

all: games graphicals core

core: $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)

games:
	make -C ./games

graphicals:
	make -C ./lib

clean:
	make clean -C ./games
	make clean -C ./lib
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./games
	make fclean -C ./lib
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re core graphicals games
