# ************************************************************************************************ #
#                                                                                                  #
#    Makefile                                            :::     :::    :::::::::     :::::::::    #
#                                                       :+:     :+:   :+:       +:   :+:           #
#    By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+            #
#                 <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#         #
#                                                    +#+     +#+           +#+    +#+              #
#    Created: 2019/07/08 07:33:53 by cdraugr-       #+#     #+#   +#       #+#   #+#               #
#    Updated: 2019/09/28 16:41:38 by cdraugr-      ###     ###     #########    #########.ru       #
#                                                                                                  #
# ************************************************************************************************ #

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
FLAGS = -std=c++17 -Wall -Wextra -Werror

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
