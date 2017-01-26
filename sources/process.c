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
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	else
		return (NULL);
}

void		read_dir(t_arg *arg, t_ls *data)
{
	DIR 	*fd;
	struct 	dirent *dir;
	struct 	stat file_stat;
	t_file *file;

	fd = 0;
	dir = NULL;
	file = NULL;
	if (arg)
	{
		fd = opendir(arg->name_dir);
		if (fd)
		{
			while ((dir = readdir(fd)))
			{
				ft_printf("format_path = {%s}\n", format_path(arg->name_dir, dir->d_name));
				if (lstat(format_path(arg->name_dir, dir->d_name), &file_stat) == 0)
				{
					file = new_file(dir, &file_stat, arg->name_dir);
					ft_printf("name = {%s}\ntype = {%s}\nfull_path = {%s}\n\n", file->name, ((file->is_dir) ? "Directorie" : "File") , file->path);
				}
			//	ft_putendl(dir->d_name);
			//	if (!is_current_dir(dir->d_name) && data->opt->br && dir->d_type == 4)
			//		read_dir(new_dir(arg->name_dir, dir->d_name), data);
			}
		}
	}
	(void)data;
}

void		ls_process(t_ls *data)
{
	t_arg	*arg;

	arg = data->arg;
	while (arg)
	{
		read_dir(arg, data);
		arg = arg->next;
	}
}