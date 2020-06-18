# Project executable
NAME := GroebnerTest.out

# Paths
INCDIR := ./includes/
SRCDIR := ./srcs/
OBJDIR := ./obj/

# Srcs, objs
SRCNAMES :=	main.cpp \
			help_functions.cpp \
			test_Rational.cpp \
			test_Modular.cpp \
			test_Monomial.cpp \
			test_Term.cpp \
			test_TermOrder.cpp \
			test_Polynomial.cpp \
			test_PolynomialOrder.cpp \
			test_PolynomialSet.cpp \
			test_Sigma.cpp \
			test_SigmaTime.cpp \
			test_CriticalPair.cpp \
			test_FastGB.cpp

SRC := $(addprefix $(SRCDIR), $(SRCNAMES))
OBJ := $(addprefix $(OBJDIR), $(SRCNAMES:.cpp=.o))

# GroebnerLib
LIBDIR := ../GroebnerLib/
LIBINCDIR := $(LIBDIR)/includes/
LIB := $(LIBDIR)/GroebnerBasis.a

# Compilation commands and flags
CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror

.PHONY: all fclean clean

all: $(NAME)

$(NAME): $(OBJDIR) $(LIB) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@$(CC) $(FLAGS) -I $(INCDIR) -I $(LIBINCDIR) -c $< -o $@

$(LIB):
	@make -C $(LIBDIR)

clean:
	@make -C $(LIBDIR) clean
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@make -C $(LIBDIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all
