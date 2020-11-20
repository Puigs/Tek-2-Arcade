##
## EPITECH PROJECT, 2020
## Makefile SFML
## File description:
## Makefile
##

NAME	= lib_arcade_nibbler.so

CXX	= g++

RM	= rm -f

SRCS	= 		src/Nibbler.cpp


OBJS	= $(SRCS:.cpp=.o)

CXXFLAGS =    -w -Wall -Wextra -fPIC -g3

all: $(NAME)

$(NAME): $(OBJS)
		$(CXX) -shared $(OBJS) -o ../$(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
