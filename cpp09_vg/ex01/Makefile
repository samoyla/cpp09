
NAME = RPN

SRCS = main.cpp RPN.cpp

RM = rm -rf

OBJS = ${SRCS:.cpp=.o}

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 

%.o: %.cpp
	${CXX} ${CXXFLAGS} $< -c -o $@ 

${NAME} : ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

all : ${NAME}

clean : 
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
