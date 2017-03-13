/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:34:39 by dgalide           #+#    #+#             */
/*   Updated: 2017/02/28 13:34:42 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			set_first_right(t_file *file, struct stat *file_stat)
{
	int		val;

	val = file_stat->st_mode;
	if (S_ISBLK(val))
		file->first_right = 'b';
	else if (S_ISCHR(val))
		file->first_right = 'c';
	else if (S_ISDIR(val))
		file->first_right = 'd';
	else if (S_ISFIFO(val))
		file->first_right = 'p';
	else if (S_ISLNK(val))
		file->first_right = 'l';
	else if (S_ISREG(val))
		file->first_right = '-';
	else if (S_ISSOCK(val))
		file->first_right = 's';
	else
		file->first_right = '-';
}

void			set_byte_blocks(t_file **file, t_ls *data)
{
	t_file		*tmp;
	int			byte_blocks;
	struct stat	file_stat;

	byte_blocks = 0;
	tmp = *file;
	(void)data;
	while (tmp)
	{
		if (!lstat(tmp->path, &file_stat) && (tmp->name[0] != '.' ||
			(tmp->name[0] == '.' && data->opt->a)))
			byte_blocks += file_stat.st_blocks;
		tmp = tmp->next;
	}
	tmp = *file;
	while (tmp)
	{
		tmp->byte_blocks = byte_blocks;
		tmp = tmp->next;
	}
}

void			hard_link_handler(t_file *new)
{
	char	tmp[258];
	size_t	len;

	len = 258;
	if (new->first_right == 'l')
	{
		len = readlink(new->path, tmp, len);
		tmp[len] = '\0';
		new->sym_link = ft_strdup(tmp);
	}
	else
		new->sym_link = NULL;
}

void			read_dir(char *path, t_ls *data)
{
	DIR				*fd;
	struct dirent	*dir;
	struct stat		file_stat;
	t_file			*file;

	fd = 0;
	dir = NULL;
	file = NULL;
	if (path)
	{
		fd = opendir(path);
		if (fd)
		{
			while ((dir = readdir(fd)))
				if (lstat(format_path(path, dir->d_name), &file_stat) == 0)
					add_file(new_file(dir, &file_stat, path, data), &file);
			closedir(fd);
			print_manager(file, data);
			if (data->opt->br)
				find_dir(&file, data);
		}
		else
			error_handler(path, data, 0);
	}
}

void			ls_process(t_ls *data)
{
	t_arg	*arg;

	arg = data->arg;
	if (!arg)
	{
		add_arg(data, ".");
		arg = data->arg;
	}
	while (arg)
	{
		read_dir(arg->name_dir, data);
		arg = arg->next;
	}
}
