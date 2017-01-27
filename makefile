NAME = ft_ls
LIB = libft/libft.a 

SRC = 	sources/main.c 												\
		sources/init_data.c											\
		sources/parse.c												\
		sources/parse_opt.c											\
		sources/parse_file.c										\
		sources/readdir.c											\
		sources/process.c											\
		sources/print_manager.c 									\
		sources/sort.c
		
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -g -fsanitize=address
CG = \033[92m 
CY =  \033[93m
CE = \033[0m
CB = \033[34m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[K$(CY)[ft_ls] :$(CE) $(CG)Creating Library$(CE)\033[1A";
	-@make -C libft
	@echo "\033[K$(CY)[ft_ls] :$(CE) $(CG)Compiling ft_ls ...$(CE)";
	@gcc -o $(NAME) $(FLAG) $(SRC) $(LIB)

%.o: %.c
	@echo "\033[K$(CY)[ft_ls] :$(CE) $(CG)Compiling $<$(CE) \033[1A";
	@gcc $(FLAG) -c $< -o $@

clean:
	@echo "\033[K$(CY)[ft_ls] :$(CE) $(CG)Cleaning Library ...$(CE)\033[1A";
	-@make clean -C libft
	@echo "\033[K$(CY)[ft_ls] :$(CE) $(CG)Cleaning ft_ls objects$(CE)\033[1A";
	@/bin/rm -rf $(OBJ)

fclean: clean
	@echo "\033[K$(CY)[ft_ls] :$(CE) $(CG)FCleaning Library ...$(CE)\033[1A";
	@echo "\033[K$(CY)[ft_ls] :$(CE) $(CG)Cleaning ft_ls ...$(CE)\033[1A";
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
