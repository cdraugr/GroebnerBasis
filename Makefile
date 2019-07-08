# ************************************************************************************************ #
#                                                                                                  #
#    Makefile                                            :::     :::    :::::::::     :::::::::    #
#                                                       :+:     :+:   :+:       +:   :+:           #
#    By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+            #
#                 <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#         #
#                                                    +#+     +#+           +#+    +#+              #
#    Created: 2019/07/08 07:33:53 by cdraugr-       #+#     #+#   +#       #+#   #+#               #
#    Updated: 2019/07/08 08:35:53 by cdraugr-      ###     ###     #########    #########.ru       #
#                                                                                                  #
# ************************************************************************************************ #


CC = g++

NAME = Test.out

CFLAGS = -std=c++17 -Wall -Wextra -Werror -O2

HEADERS = includes/Monomial.h includes/Tests.h

SOURCES = srcs/Monomial.cpp srcs/Tests.cpp main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

COMP = $(CC) $(SOURCES) $(CFLAGS) -o

all:
	@$(COMP) $(NAME)

clean:
	@rm -R $(NAME)

