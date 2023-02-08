NAME = minitalk

HEADER = minitalk.h
lib = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_server = server.c
OBJ_server = $(SRC_server:.c=.o)

SRC_client = client.c
OBJ_client = $(SRC_client:.c=.o)


%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

all: 	$(NAME)

$(NAME): lib server client

client: $(OBJ_client) $(HEADER) $(lib)
	@$(CC) $(CFLAGS) $(OBJ_client) -L./libft -lft -o client
	@echo "Client compiled"

server: $(OBJ_server) $(HEADER) $(lib)
	@$(CC) $(CFLAGS) $(SRC_server) -L./libft -lft -o server
	@echo "Server compiled"

re: fclean all

fclean:
	@rm -f $(OBJ_server) $(OBJ_client)
	@rm -f server client
	@make -C libft fclean
	@echo "Server, client and minitalk objects cleaned"

clean:
	@rm -f $(OBJ_server) $(OBJ_client)
	@make -C libft clean
	@echo "Minitalk objects cleaned"

bonus: $(NAME)

lib: 
	@make -C libft

.PHONY: all re clean fclean
