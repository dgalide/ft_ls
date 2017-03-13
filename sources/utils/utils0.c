/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 03:48:06 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/13 03:48:07 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int			is_current(char *name)
{
	if (name && ft_strlen(name) >= 1 && name[ft_strlen(name) - 1] == '.')
		return (1);
	else if (name && ft_strlen(name) >= 2 && name[ft_strlen(name) - 1] == '.'
		&& name[ft_strlen(name) - 2] == '.')
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
				((tmp->name)[0] != '.' || ((tmp->name)[0] != '.' &&
					data->opt->a)))
				read_dir(tmp->path, data);
			tmp = tmp->next;
		}
	}
}

int			is_parent_dir(char *file)
{
	if (file && ft_strlen(file) == 2 && file[0] == '.' && file[1] == '.')
		return (1);
	else
		return (0);
}

int			is_current_dir(char *file)
{
	if (file && ft_strlen(file) == 1 && file[0] == '.')
		return (1);
	else
		return (0);
}
