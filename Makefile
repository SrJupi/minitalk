NAME = minitalk

HEADER = minitalk.h
lib = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_server = server.c str_utils.c
OBJ_server = $(SRC_server:.c=.o)

SRC_BONUS_server = server_bonus.c str_utils_bonus.c
OBJ_BONUS_server = $(SRC_BONUS_server:.c=.o)

SRC_client = client.c
OBJ_client = $(SRC_client:.c=.o)

SRC_BONUS_client = client_bonus.c
OBJ_BONUS_client = $(SRC_BONUS_client:.c=.o)


%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

all: 	lib server client

$(NAME): lib server client

client: $(OBJ_client) $(HEADER) $(lib)
	@$(CC) $(CFLAGS) $(OBJ_client) -L./libft -lft -o client
	@echo "Client compiled"

server: $(OBJ_server) $(HEADER) $(lib)
	@$(CC) $(CFLAGS) $(OBJ_server) -L./libft -lft -o server
	@echo "Server compiled"

bonus: lib server_bonus client_bonus

client_bonus: $(OBJ_BONUS_client) $(HEADER) $(lib)
	@$(CC) $(CFLAGS) $(OBJ_BONUS_client) -L./libft -lft -o client_bonus
	@echo "Client compiled"

server_bonus: $(OBJ_BONUS_server) $(HEADER) $(lib) 
	@$(CC) $(CFLAGS) $(OBJ_BONUS_server) -L./libft -lft -o server_bonus
	@echo "Server compiled"

re: fclean all

re_bonus: fclean bonus

fclean:
	@rm -f $(OBJ_server) $(OBJ_client) $(OBJ_BONUS_server) $(OBJ_BONUS_client)
	@rm -f server client server_bonus client_bonus
	@make -C libft fclean
	@echo "Server, client and minitalk objects cleaned"

clean:
	@rm -f $(OBJ_server) $(OBJ_client) $(OBJ_BONUS_server) $(OBJ_BONUS_client)
	@make -C libft clean
	@echo "Minitalk objects cleaned"

lib: 
	@make -C libft

.PHONY: all re re_bonus clean fclean
