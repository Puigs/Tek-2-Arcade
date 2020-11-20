##
## EPITECH PROJECT, 2020
## Makefile SDL
## File description:
## Makefile
##

NAME	= lib_arcade_sdl.so

CPP	= g++

RM	= rm -f

SRCS	= ./srcs/Sdl.cpp \
		./srcs/Info.cpp \
		./srcs/InitTab.cpp \
		./srcs/Score.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./pp
CPPFLAGS += -w -Wall -Wextra -fPIC -rdynamic -g3
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(NAME)

$(NAME): $(OBJS)
	 $(CPP) -shared $(OBJS) -o ../$(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
