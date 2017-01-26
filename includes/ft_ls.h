/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:30:17 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/24 16:30:18 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS 

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# define D_DIR (struct dirent)

typedef struct  		s_opt
{
		int				l;
		int				sr;
		int				br;
		int				a;
		int				t;
}						t_opt;

typedef struct 			s_arg
{
	struct s_arg		*next;
	struct s_arg		*prev;
	char				*name_dir;
}						t_arg;

typedef struct 			s_file
{
	char				*path;
	char				*name;
	int 				is_dir;
	struct s_file		*next;
	struct s_file		*prev;
}						t_file;

typedef struct 			s_ls
{
	t_opt				*opt;
	t_arg				*arg;
	int					nb_file;
}						t_ls;

int						main(int ac, char **av);
int						init_data(t_ls *ls, char **av, int ac);
int 					parse(t_ls *ls, char *arg);
int 					parse_opt(t_ls *ls, char *str);
int 					parse_file(t_ls *ls, char *str);
void					ls_process(t_ls *data);
char					*recursive_read(t_ls *data, char *name, int stop);
int						add_file(t_ls *data, char *name);
int 					is_current_dir(char *name);

#endif