CC = g++

NAME = GroebnerTest.out

SOURCES = ./srcs/main.cpp\
		./srcs/help_functions.cpp\
		./srcs/test_Rational.cpp\
		./srcs/test_Modular.cpp\
		./srcs/test_Monomial.cpp\
		./srcs/test_Term.cpp\
		./srcs/test_TermOrder.cpp\
		./srcs/test_Polynomial.cpp\
		./srcs/test_PolynomialOrder.cpp\
		./srcs/test_PolynomialSet.cpp\
		./srcs/test_Sigma.cpp\
		./srcs/test_SigmaTime.cpp

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
