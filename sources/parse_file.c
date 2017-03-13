/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:49:45 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/24 17:50:36 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				add_arg(t_ls *data, char *name)
{
	t_arg		*new_file;
	t_arg		*tmp;

	tmp = NULL;
	new_file = (t_arg *)malloc(sizeof(t_arg));
	if (!new_file)
		return (0);
	new_file->name_dir = ft_strdup(name);
	new_file->next = NULL;
	new_file->prev = NULL;
	if (!data->arg)
		data->arg = new_file;
	else
	{
		tmp = data->arg;
		while (tmp->next)
			tmp = tmp->next;
		new_file->prev = tmp;
		tmp->next = new_file;
	}
	return (1);
}

int 				parse_arg(t_ls *data, char *str)
{
	DIR				*fd;

	fd = 0;
	if (str && (fd = opendir(str)))
	{
		closedir(fd);
		if (!add_arg(data, str))
			return (0);
		else
			return (1);
	}
	else
	{
		error_handler(str, data, 1);
		return (0);
	}
}

// t_arg		*new_dir(char *path, char *dir)
// {
// 	t_arg	*new;
// 	char	*tmp;

// 	new = (t_arg *)malloc(sizeof(t_arg));
// 	tmp = NULL;
// 	if (path && new)
// 	{
// 		tmp = ft_strjoin(path,
// 			(path[ft_strlen(path) - 1] != '/') ? "/" : NULL);
// 		new->next = NULL;
// 		new->prev = NULL;
// 		new->name_dir = ft_strjoin_free(&tmp, &dir, 1, 0);
// 		return (new);
// 	}
// 	else
// 		return (NULL);
// }