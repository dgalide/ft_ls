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

int				ft_check_cols(int tmp)
{
	int i;

	i = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}

t_arg		*new_dir(char *path, char *dir)
{
	t_arg	*new;
	char	*tmp;

	new = (t_arg *)malloc(sizeof(t_arg));
	tmp = NULL;
	if (path && new)
	{
		tmp = ft_strjoin(path,
			(path[ft_strlen(path) - 1] != '/') ? "/" : NULL);
		new->next = NULL;
		new->prev = NULL;
		new->name_dir = ft_strjoin_free(&tmp, &dir, 1, 0);
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
		tmp = ft_strjoin(curr_path,
			(curr_path[ft_strlen(curr_path) - 1] != '/') ? "/" : NULL);
		return (ft_strjoin_free(&tmp, &name_file, 1, 0));
	}
	else
		return (NULL);
}

int 		is_parent_dir(char *file)
{
	if (file && ft_strlen(file) == 2 && file[0] == '.' && file[1] == '.')
		return (1);
	else
		return (0);
}

int 		is_current_dire(char *file)
{
	if (file && ft_strlen(file) == 1 && file[0] == '.')
		return (1);
	else
		return (0);
}

void 		set_first_right(t_file *file, struct stat *file_stat)
{
	int val;

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

void		set_byte_blocks(t_file **file, t_ls *data)
{
	t_file	*tmp;
	int byte_blocks;
	struct 	stat file_stat;

	byte_blocks = 0;
	tmp = *file;
	(void)data;
	while (tmp)
	{
		if (!lstat(tmp->path, &file_stat) && (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a)))
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

void		hard_link_handler(t_file *new)
{
	char *tmp;
	size_t len;

	len = 0;
	tmp = NULL;
	if (new->first_right == 'l')
	{
		ft_printf("YOYYOYOYYOYOYO\n");
		readlink(new->path, tmp, len);
	
		ft_printf("{%s}\n", tmp);
	}
	else
		new->sym_link = NULL;
}

t_file		*new_file(struct dirent *dir, struct stat *file_stat, char *cur_path, t_ls *data)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (cur_path && file_stat && new)
	{
		new->name = ft_strdup(dir->d_name);
		new->bool_parent = is_parent_dir(dir->d_name);
		new->bool_current = is_current_dire(dir->d_name);
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
			if (tmp->is_dir && !is_current(tmp->name) &&
				((tmp->name)[0] != '.' || ((tmp->name)[0] != '.' && data->opt->a)))
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
		//ft_printf("%s\n", path);
		if (fd)
		{
			while ((dir = readdir(fd)))
			{
				if (lstat(format_path(path, dir->d_name), &file_stat) == 0)
					add_file(new_file(dir, &file_stat, path, data), &file);
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
