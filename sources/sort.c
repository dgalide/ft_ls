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
	int 			bool_alpha;

	tmp = file;
	bool_alpha = 1;
	if (tmp)
	{
		while (tmp->next)
		{
			if (ft_strcmp(tmp->next->name, tmp->name) > 0)
				bool_alpha = 0;
			tmp = tmp->next;
		}
	}
	return ((bool_alpha) ? 1 : 0);
}

int 				is_sort_date(t_file *file)
{
	t_file			*tmp;
	int 			bool_time;

	tmp = file;
	bool_time = 1;
	if (tmp)
	{
		while (tmp->next)
		{
			if (tmp->time < tmp->next->time)
				bool_time = 0;
			tmp = tmp->next;
		}
	}
	return ((bool_time) ? 1 : 0);
}

void				swap_file(t_file *a, t_file *b, t_file *begin)
{
	t_file 			*tmp;
	t_file			*tmp1;
	t_file			*tmp2;

	tmp = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	if (a && b)
	{
		tmp = a->prev;
		tmp1 = b->next;
		tmp2 = a;
		a->next = tmp1;
		a->prev = b;
		b->next = tmp2;
		b->prev = tmp;
		if (tmp)
			tmp->next = b;
		else
			begin = b;
		if (tmp1)
			tmp1->prev = tmp2;
	}
}

void				debug_print(t_file *file)
{
	t_file *tmp;

	tmp = file;
	ft_putendl("\n-- DEBUG --");
	if (tmp)
	{
		while (tmp)
		{
			ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
	ft_putendl("\n-- END DEBUG --");
}

void 				sort_alpha(t_file **file)
{
	t_file			*tmp;

	tmp = *file;
	debug_print(*file);
	if (tmp)
	{
		while (!is_sort_alpha((*file)))
		{
			if (!tmp || !tmp->next)
				tmp = (*file);
			debug_print(*file);
			ft_putchar('I');
			if (tmp && tmp->next && ft_strcmp(tmp->next->name, tmp->name) > 0)
				swap_file(tmp, tmp->next, (*file));
			ft_putchar('J');
			debug_print(*file);
			tmp = tmp->next;
			//if ((*file) && (*file)->name && tmp && tmp->name)
			//	ft_printf("sort_alpha name = {%s}{%s}\n", (*file)->name, tmp->name);
		}
	}
	debug_print(*file);
}

void 				sort_date(t_file *file)
{
	t_file			*tmp;

	tmp = file;
	if (tmp)
	{
		while (!is_sort_date(file))
		{
			if (!tmp || !tmp->next)
				tmp = file;
			if (tmp && tmp->next && tmp->time < tmp->next->time)
				swap_file(tmp, tmp->next, file);
			tmp = tmp->next;
		}
	}
}