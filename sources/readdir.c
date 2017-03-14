/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 09:34:39 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/14 09:34:41 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		read_dir_extend(DIR *fd, t_file *file, t_ls *data, char *path)
{
	struct dirent	*dir;
	struct stat		file_stat;

	while ((dir = readdir(fd)))
	{
		if (lstat(format_path(path, dir->d_name), &file_stat) == 0)
			add_file(new_file(dir, &file_stat, path, data), &file);
		else
			error_handler(path, data, 0);
	}
	closedir(fd);
	print_list(file);
	print_manager(file, data);
	print_list(file);
	if (data->opt->br)
		find_dir(file, data);
}

void			read_dir(char *path, t_ls *data)
{
	DIR				*fd;
	t_file			*file;

	fd = 0;
	file = NULL;
	if (path)
	{
		fd = opendir(path);
		if (fd)
			read_dir_extend(fd, file, data, path);
		else
			error_handler(path, data, 0);
	}
}