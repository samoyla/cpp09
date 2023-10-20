# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masamoil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 12:19:53 by masamoil          #+#    #+#              #
#    Updated: 2023/04/17 12:20:13 by masamoil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

SRCS = main.cpp BitcoinExchange.cpp

OBJS = ${SRCS:.cpp=.o}

RM = rm -rf

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 

all: ${NAME}

%.o:	%.cpp
		${CXX} ${CXXFLAGS} -c $< -o $@

${NAME}: ${OBJS}
		${CXX} ${CXXFLAGS} ${OBJS} -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
