# ************************************************************************************************ #
#                                                                                                  #
#    Makefile                                            :::     :::    :::::::::     :::::::::    #
#                                                       :+:     :+:   :+:       +:   :+:           #
#    By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+            #
#                 <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#         #
#                                                    +#+     +#+           +#+    +#+              #
#    Created: 2019/07/08 07:33:53 by cdraugr-       #+#     #+#   +#       #+#   #+#               #
#    Updated: 2019/07/26 18:33:13 by cdraugr-      ###     ###     #########    #########.ru       #
#                                                                                                  #
# ************************************************************************************************ #

CC = g++

NAME = GroebnerBasis.a

FLAGS = -std=c++17 -Wall -Wextra -Werror -c

SOURCES = ./srcs/Rational.cpp\
			./srcs/Lib.cpp\
			./srcs/Monomial.cpp

OBJECTS = ./Rational.o\
			./Lib.o\
			./Monomial.o

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
