##
## EPITECH PROJECT, 2020
## Makefile SFML
## File description:
## Makefile
##

NAME	= lib_arcade_sfml.so

CXX	= g++

RM	= rm -f

SRCS	= 	src/Arcade_Sfml.cpp			\
			src/Score.cpp			\
			src/Info.cpp			\


OBJS	= $(SRCS:.cpp=.o)

SFFLAGS =    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXXFLAGS =    -w -Wall -Wextra -fPIC -g3

all: $(NAME)

$(NAME): $(OBJS)
		$(CXX) -shared $(OBJS) -o ../$(NAME) $(LDFLAGS) $(SFFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
