CC = g++

NAME = GroebnerTest.out

SOURCES = ./srcs/main.cpp\
		./srcs/Tests.cpp

PATH_LIB = ../GroebnerLib/
SOURCES_LIB = ../GroebnerLib/GroebnerBasis.a

FLAGS = -std=c++17 -Wall -Wextra -Werror
FLAGS_LIB = -I ../GroebnerLib/includes/

all: $(NAME)

$(NAME):
	@make -C $(PATH_LIB)
	@$(CC) $(FLAGS) $(FLAGS_LIB) $(SOURCES) $(SOURCES_LIB) -o $(NAME)

clean:
	@make clean -C $(PATH_LIB)

fclean: clean
	@make fclean -C $(PATH_LIB)
	@/bin/rm -f $(NAME)

re: fclean all
