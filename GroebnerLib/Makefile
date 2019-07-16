# ************************************************************************************************ #
#                                                                                                  #
#    Makefile                                            :::     :::    :::::::::     :::::::::    #
#                                                       :+:     :+:   :+:       +:   :+:           #
#    By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+            #
#                 <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#         #
#                                                    +#+     +#+           +#+    +#+              #
#    Created: 2019/07/08 07:33:53 by cdraugr-       #+#     #+#   +#       #+#   #+#               #
#    Updated: 2019/07/16 21:22:47 by cdraugr-      ###     ###     #########    #########.ru       #
#                                                                                                  #
# ************************************************************************************************ #

CC = g++

NAME = GroebnerBasis.a

FLAGS = -std=c++17 -Wall -Wextra -Werror -c

SOURCES = ./srcs/Rational.cpp\
		./srcs/Monomial.cpp\
		./srcs/MonomialOrder.cpp\

OBJECTS = ./Rational.o\
		./Monomial.o\
		./MonomialOrder.o

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) $(SOURCES)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@make clean

clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
