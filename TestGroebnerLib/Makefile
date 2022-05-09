# Project executable
NAME := GroebnerTest.out

# Paths
INCDIR := ./includes/
SRCDIR := ./srcs/
OBJDIR := ./obj/

# Srcs, objs
SRCNAMES :=	main.cpp \
			utils.cpp \
			test_fields.cpp \
			test_rational.cpp \
			test_modular.cpp \
			test_term.cpp \
			test_monomial.cpp \
			test_monomial_order.cpp \
			test_polynomial.cpp \
			test_polynomial_order.cpp \
			test_polynomial_set.cpp \
			test_root.cpp \
			test_root_time.cpp \
			test_critical_pair.cpp \
			test_f4_gb.cpp

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
