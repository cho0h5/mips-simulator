NAME = mips_simulator
CC = g++
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.cpp
OBJS = $(SRCS:.cpp=.o)
SRC_DIR = ./srcs
INCLUDE = -Iincludes/
HEADERS = 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
