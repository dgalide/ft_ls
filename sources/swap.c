/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 04:30:09 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/13 04:30:10 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			is_neighbours(t_file *a, t_file *b)
{
	return ((a->next == b && b->prev == a) || (a->prev == b && b->next == a));
}

void		refresh_pointers(t_file *a)
{
	if (a->prev != NULL)
		a->prev->next = a;
	if (a->next != NULL)
		a->next->prev = a;
}

void		swap(t_file *a, t_file *b)
{
	t_file	*tab_ptr[4];

	tab_ptr[0] = a->prev;
	tab_ptr[1] = b->prev;
	tab_ptr[2] = a->next;
	tab_ptr[3] = b->next;
	if (is_neighbours(a, b))
	{
		a->prev = tab_ptr[2];
		b->prev = tab_ptr[0];
		a->next = tab_ptr[3];
		b->next = tab_ptr[1];
	}
	else
	{
		a->prev = tab_ptr[1];
		b->prev = tab_ptr[0];
		a->next = tab_ptr[3];
		b->next = tab_ptr[2];
	}
	refresh_pointers(a);
	refresh_pointers(b);
}
