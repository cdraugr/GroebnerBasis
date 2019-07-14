# ************************************************************************************************ #
#                                                                                                  #
#    Makefile                                            :::     :::    :::::::::     :::::::::    #
#                                                       :+:     :+:   :+:       +:   :+:           #
#    By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+            #
#                 <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#         #
#                                                    +#+     +#+           +#+    +#+              #
#    Created: 2019/07/08 07:33:53 by cdraugr-       #+#     #+#   +#       #+#   #+#               #
#    Updated: 2019/07/14 11:31:07 by cdraugr-      ###     ###     #########    #########.ru       #
#                                                                                                  #
# ************************************************************************************************ #


CC = g++

NAME = GroebnerBasis.out

CFLAGS = -std=c++17 -Wall -Wextra -Werror

SOURCES = srcs/Rational.cpp\
		srcs/Monomial.cpp\
		srcs/MonomialOrder.cpp\
		srcs/Tests.cpp\
		main.cpp

COMP = $(CC) $(SOURCES) $(CFLAGS) -o

all:
	@$(COMP) $(NAME)

clean:
	@rm -R $(NAME)

