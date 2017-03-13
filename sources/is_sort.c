/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 04:45:52 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/13 04:45:53 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					is_sort_alpha(t_file *file)
{
	t_file			*tmp;

	tmp = file;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) < 0)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

int					is_sort_alpha_rev(t_file *file)
{
	t_file			*tmp;

	tmp = file;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

int					is_sort_date(t_file *file, int direction)
{
	t_file			*tmp;
	int				bool_time;

	tmp = file;
	bool_time = 1;
	if (tmp)
	{
		while (tmp->next)
		{
			if ((tmp->time < tmp->next->time && !direction) ||
				(tmp->time > tmp->next->time && direction))
			{
				bool_time = 0;
			}
			tmp = tmp->next;
		}
	}
	return ((bool_time) ? 1 : 0);
}
