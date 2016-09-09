NAME = ft_ls

SRC = main.c

INC = includes/ft_ls.h

OBJ = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Wextra -Werror

LIBFT = libft/libft.a

all: name

re: fclean all

lib:
	@make -C libft

.c.o:
	$(CC) $(FLAG) -o $(OBJ) -c $(SRC) -I $(INC)

name: lib
	$(CC) $(FLAG) -o $(NAME) $(OBJ) $(LIBFT)

clean: 
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

.PHONY: all re clean fclean
