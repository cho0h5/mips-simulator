NAME = mipsvm
CC = g++
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = src/main.cpp src/memory.cpp
OBJS = $(SRCS:.cpp=.o)
SRC_DIR = ./src
INCLUDE = -Iinclude/
HEADERS = include/memory.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
