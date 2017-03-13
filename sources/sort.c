/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 16:01:38 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/27 16:01:40 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				sort_alpha(t_file **file)
{
	t_file			*tmp;
	t_file			*tmp1;

	tmp = *file;
	tmp1 = NULL;
	if (tmp)
	{
		while (!is_sort_alpha((*file)))
		{
			if (!tmp || !tmp->next)
				tmp = *file;
			if (tmp && tmp->next && ft_strcmp(tmp->name, tmp->next->name) < 0)
			{
				if (tmp == *file)
					*file = tmp->next;
				swap(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
	}
}

void				sort_alpha_rev(t_file **file)
{
	t_file			*tmp;
	t_file			*tmp1;

	tmp = *file;
	tmp1 = NULL;
	if (tmp)
	{
		while (!is_sort_alpha_rev((*file)))
		{
			if (!tmp || !tmp->next)
				tmp = *file;
			if (tmp && tmp->next && ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				if (tmp == *file)
					*file = tmp->next;
				swap(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
	}
}

void				sort_date(t_file **file)
{
	t_file			*tmp;

	tmp = *file;
	if (tmp)
	{
		while (!is_sort_date(*file, 0))
		{
			if (!tmp || !tmp->next)
				tmp = *file;
			if (tmp && tmp->next && tmp->time < tmp->next->time)
			{
				if (tmp == *file)
					*file = tmp->next;
				swap(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
	}
}

void				sort_rdate(t_file **file)
{
	t_file			*tmp;

	tmp = *file;
	if (tmp)
	{
		while (!is_sort_date(*file, 1))
		{
			if (!tmp || !tmp->next)
				tmp = *file;
			if (tmp && tmp->next && tmp->time > tmp->next->time)
			{
				if (tmp == *file)
					*file = tmp->next;
				swap(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
	}
}
