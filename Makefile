NAME = minitalk

HEADER = minitalk.h
lib = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_server = server.c str_utils.c ft_checksum.c server_receive_utils.c
OBJ_server = $(SRC_server:.c=.o)

SRC_client = client.c client_checks.c client_errors.c client_send_utils.c ft_checksum.c
OBJ_client = $(SRC_client:.c=.o)

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

all: 	lib server client
	@echo "Minitalk compiled"

$(NAME): lib server client
	@echo "Minitalk compiled"


client: $(OBJ_client) $(HEADER) $(lib)
	@$(CC) $(CFLAGS) $(OBJ_client) -L./libft -lft -o client
	@echo "Client compiled"

server: $(OBJ_server) $(HEADER) $(lib)
	@$(CC) $(CFLAGS) $(OBJ_server) -L./libft -lft -o server
	@echo "Server compiled"

bonus: lib server client
	@echo "Bonus compiled"

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

.PHONY: all re re_bonus clean fclean bonus
