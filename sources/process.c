/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 22:55:15 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/24 22:55:16 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h" 

t_arg		*new_dir(char *path, char *dir)
{
	t_arg	*new;
	char	*tmp;

	new = (t_arg *)malloc(sizeof(t_arg));
	tmp = NULL;
	if (path && new)
	{
		tmp = ft_strjoin(path, "/");
		new->next = NULL;
		new->prev = NULL;
		new->name_dir = ft_strjoin_free(&tmp, &dir, 1, 0);
		ft_printf("\n-- NEW_DIR --\n new->name_dir = {%s}\n", new->name_dir);
		return (new);
	}
	else
		return (NULL);
}

char		*format_path(char *curr_path, char *name_file)
{
	char	*tmp;

	tmp = NULL;
	if (curr_path && name_file)
	{
		tmp = ft_strjoin(curr_path, "/");
		return (ft_strjoin_free(&tmp, &name_file, 1, 0));
	}
	else
		return (NULL);
}

t_file		*new_file(struct dirent *dir, struct stat *file_stat, char *cur_path)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (cur_path && file_stat && new)
	{
		new->path = format_path(cur_path, dir->d_name);
		new->name = ft_strdup(dir->d_name);
		new->is_dir = (dir->d_type == 4) ? 1 : 0;
		new->nb_hard_link = file_stat->st_nlink;
		(getpwuid(file_stat->st_uid)) ?
		(new->name_usr = getpwuid(file_stat->st_uid)->pw_name) :
		(new->name_usr = ft_strdup(ft_itoa(file_stat->st_uid, 10)));
		(getgrgid(file_stat->st_gid)->gr_name) ?
		(new->name_grp = getgrgid(file_stat->st_gid)->gr_name) :
		(new->name_grp = ft_strdup(ft_itoa(file_stat->st_gid, 10)));
		new->inode_nu = file_stat->st_ino;
		new->right_nu = file_stat->st_mode;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	else
		return (NULL);
}

void		add_file(t_file *new, t_file **begin)
{
	t_file	*tmp;

	tmp = *begin;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*begin = new;
}

int 		is_current(char *name)
{
	if (name && ft_strlen(name) >= 1 && name[ft_strlen(name) - 1] == '.')
		return (1);
	else if (name && ft_strlen(name) >= 2 && name[ft_strlen(name) - 1] == '.' && name[ft_strlen(name) - 2] == '.')
		return (1);
	else
		return (0);
}

void		find_dir(t_file **file, t_ls *data)
{
	t_file	*tmp;

	tmp = *file;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->is_dir && !is_current(tmp->name))
				read_dir(tmp->path, data);
			tmp = tmp->next;
		}
	}
}

void		read_dir(char *path, t_ls *data)
{
	DIR 	*fd;
	struct 	dirent *dir;
	struct 	stat file_stat;
	t_file *file;

	fd = 0;
	dir = NULL;
	file = NULL;
	if (path)
	{
		fd = opendir(path);
		if (fd)
		{
			while ((dir = readdir(fd)))
			{
				//ft_putendl(dir->d_name);
				if (lstat(format_path(path, dir->d_name), &file_stat) == 0)
					add_file(new_file(dir, &file_stat, path), &file);
			}
			closedir(fd);
			print_manager(file, data);
			if (data->opt->br)
				find_dir(&file, data);
		}
	}
}

void		ls_process(t_ls *data)
{
	t_arg	*arg;

	arg = data->arg;
	while (arg)
	{
		read_dir(arg->name_dir, data);
		arg = arg->next;
	}
}