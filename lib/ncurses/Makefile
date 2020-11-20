##
## EPITECH PROJECT, 2020
## Makefile ncurses
## File description:
## Makefile
##

NAME	= lib_arcade_ncurses.so

CC	= g++

RM	= rm -f

SRCS	= 	srcs/Info.cpp \
			srcs/NCurses.cpp \
			srcs/Score.cpp \
			srcs/InitTab.cpp


OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I.
CPPFLAGS += -W -Wall -Wextra -fPIC -rdynamic
LDFLAGS = -shared -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o ../$(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
