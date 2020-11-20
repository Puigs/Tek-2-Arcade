##
## EPITECH PROJECT, 2020
## Pacman
## File description:
## Makefile
##

NAME	= lib_arcade_pacman.so

CXX	= g++

RM	= rm -f

SRCS	= ./srcs/Entity.cpp \
	./srcs/Ghost.cpp \
	./srcs/Map.cpp \
	./srcs/Pacman.cpp \
	./srcs/Player.cpp \
	./srcs/InitTab.cpp \
	./srcs/Info.cpp \
	./srcs/Score.cpp

OBJS    = $(SRCS:.cpp=.o)

CXXFLAGS =    -Werror -w -Wall -Wextra -fPIC -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -shared $(OBJS) -o ../$(NAME) $(LDFLAGS) $(SFFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
