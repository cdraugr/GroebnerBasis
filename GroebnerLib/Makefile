# Project executable
NAME := GroebnerBasis.a

# Paths
INCDIR := ./includes/
SRCDIR := ./srcs/

# Srcs, objs
SRCNAMES := Rational.cpp \
			Lib.cpp \
			Monomial.cpp

SRC := $(addprefix $(SRCDIR), $(SRCNAMES))
OBJ := $(SRCNAMES:.cpp=.o)

# Compilation commands and flags
CC := g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -O2

.PHONY: all fclean clean

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $(OBJ)
	@ranlib $@

%.o: $(SRCDIR)%.cpp
	@$(CC) $(FLAGS) -I $(INCDIR) -c $?

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
