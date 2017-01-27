/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:30:17 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/27 00:31:25 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS 

# include "../libft/includes/libft.h" 
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>

# define D_DIR (struct dirent)

typedef struct  		s_opt
{
		int				l;
		int				sr;
		int				br;
		int				a;
		int				t;
		int 			bt;
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
	int 				denied_acces;
	int 				nb_hard_link;
	char 				*name_usr;
	char 				*name_grp;
	int 				bool_current;
	int 				bool_parent;
	int					inode_nu;
	mode_t 				right_nu;
	int 				is_dir;
	int     			st_size;
	char 	   			*mtime;
	long 				time;
	struct s_file		*next;
	struct s_file		*prev;
}						t_file;

typedef struct 			s_ls
{
	t_opt				*opt;
	t_arg				*arg;
	t_file 				*file;
	int 				byte_blocks;
}						t_ls;

int						main(int ac, char **av);
int						init_data(t_ls *ls, char **av, int ac);
int 					parse(t_ls *ls, char *arg);
int 					parse_opt(t_ls *ls, char *str);
int 					parse_arg(t_ls *ls, char *str);
void					ls_process(t_ls *data);
char					*recursive_read(t_ls *data, char *name, int stop);
int						add_arg(t_ls *data, char *name);
int 					is_current_dir(char *name);
void					read_dir(char *path, t_ls *data);
void					print_manager(t_file *file, t_ls *data);
int 					is_sort_date(t_file *file);
int 					is_sort_alpha(t_file *file);
void 					sort_alpha(t_file **file);
void 					sort_date(t_file *file);

#endif