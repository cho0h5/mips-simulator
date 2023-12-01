NAME = mipsvm
CC = g++
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.cpp src/memory.cpp src/computer.cpp src/registers.cpp
OBJS = $(SRCS:.cpp=.o)
SRC_DIR = ./src
INCLUDE = -Iinclude/
HEADERS = include/memory.h include/computer.h include/registers.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

test: all
	./$(NAME) testcase/print_1218.bin

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
