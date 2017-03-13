/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 03:39:15 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/13 03:39:16 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

t_file		*new_file(struct dirent *dir, struct stat *file_stat,
	char *cur_path, t_ls *data)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (cur_path && file_stat && new)
	{
		new->name = ft_strdup(dir->d_name);
		new->bool_parent = is_parent_dir(dir->d_name);
		new->bool_current = is_current_dir(dir->d_name);
		new->path = format_path(cur_path, dir->d_name);
		new->parent_path = ft_strdup(cur_path);
		new->st_size = (int)file_stat->st_size;
		new->mtime = ft_strdup(ctime(&(file_stat->st_mtime)));
		new->time = file_stat->st_mtime;
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
		set_first_right(new, file_stat);
		hard_link_handler(new);
		(void)data;
		if (S_ISCHR(new->right_nu) || S_ISBLK(new->right_nu))
		{
			new->major = major(file_stat->st_rdev);
			new->minor = minor(file_stat->st_rdev);
		}
		else
		{
			new->major = 0;
			new->minor = (int)file_stat->st_size;
		}
		return (new);
	}
	else
		return (NULL);
}