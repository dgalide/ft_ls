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

int 				is_sort_alpha(t_file *file)
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

int 				is_sort_alpha_rev(t_file *file)
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

int 				is_sort_date(t_file *file, int direction)
{
	t_file			*tmp;
	int 			bool_time;

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

void				debug_print(t_file *file)
{
	t_file *tmp;
	static int i = 0;

	tmp = file;
	ft_printf("\n-- DEBUG num[%d]--\n", i);
	if (tmp)
	{
		while (tmp)
		{
			ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	i += 1;
	ft_putendl("-- END DEBUG --\n");
}

void 				sort_alpha(t_file **file)
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

void 				sort_alpha_rev(t_file **file)
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

void 				sort_date(t_file **file)
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

void 				sort_rdate(t_file **file)
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