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

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <errno.h>
# include <time.h>
# include <stdio.h>
# include <string.h>

typedef struct		s_opt
{
	int				l;
	int				sr;
	int				br;
	int				a;
	int				t;
	int				bt;
	int				sg;
}					t_opt;

typedef struct		s_arg
{
	struct s_arg	*next;
	struct s_arg	*prev;
	char			*name_dir;
}					t_arg;

typedef struct		s_file
{
	char			*path;
	char			*parent_path;
	char			*name;
	int				denied_acces;
	int				nb_hard_link;
	char			*name_usr;
	char			*name_grp;
	int				first_right;
	int				byte_blocks;
	int				bool_current;
	int				bool_parent;
	int				inode_nu;
	int				right_nu;
	int				is_dir;
	int				st_size;
	char			*sym_link;
	char			*mtime;
	long			time;
	int				major;
	int				minor;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct		s_ls
{
	t_opt			*opt;
	t_arg			*arg;
	t_file			*file;
	int				max_minor;
	int				max_major;
	int				max_lnk;
	int				max_name;
	int				max_gid;
	int				max_uid;
	int				max_size;
}					t_ls;

int					main(int ac, char **av);
int					init_data(t_ls *ls, char **av, int ac);
void				print_right(t_file *file);
t_file				*new_file(struct dirent *dir, struct stat *file_stat,
	char *cur_path, t_ls *data);
void				add_file(t_file *new, t_file **begin);
void				read_dir(char *path, t_ls *data);
void				set_first_right(t_file *file, struct stat *file_stat);
int					check_colon(int value);
int					is_parent_dir(char *file);
void				hard_link_handler(t_file *new);
char				*format_path(char *curr_path, char *name_file);
int					check_major(t_file *file);
char				*time_handler(t_file *file, t_opt *opt);
void				print_l_mode(t_file **file, t_ls *data);
int					parse(t_ls *ls, char *arg);
int					parse_opt(t_ls *ls, char *str);
int					parse_arg(t_ls *ls, char *str);
void				set_byte_blocks(t_file **file, t_ls *data);
void				ls_process(t_ls *data);
void				error_handler(char *error, t_ls *data, int exit);
char				*recursive_read(t_ls *data, char *name, int stop);
int					add_arg(t_ls *data, char *name);
int					is_current_dir(char *name);
void				read_dir(char *path, t_ls *data);
void				find_dir(t_file *file, t_ls *data);
char				*format_path(char *curr_path, char *name_file);
void				print_manager(t_file **file, t_ls *data);
int				is_sort_date(t_file *file, int direction);
int					is_sort_alpha(t_file *file);
void				sort_alpha(t_file **file);
int					is_current(char *name);
void				sort_alpha_rev(t_file **file);
t_arg				*new_dir(char *path, char *dir);
void				sort_date(t_file **file);
void				error_handler(char *path, t_ls *data, int bool_exit);
int					is_sort_date(t_file *file, int direction);
int					is_sort_alpha_rev(t_file *file);
int					is_sort_alpha(t_file *file);
int					is_parent_dir(char *file);
void				sort_rdate(t_file **file);
void				swap(t_file *a, t_file *b);
void				define_max_field(t_file **file, t_ls *data);
int					is_current_dir(char *file);
int					ft_check_cols(int tmp);
void				print_list(t_file *file);

#endif
