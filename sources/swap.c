/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 19:52:19 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/29 19:52:20 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h" 

int is_neighbours(t_file *a, t_file *b)
{
    return (a->next == b && b->prev == a) || (a->prev == b && b->next == a);
}

void refresh_pointers(t_file *a)
{
    if (a->prev != NULL)
        a->prev->next = a;

    if (a->next != NULL)
        a->next->prev = a;
}

void swap(t_file *a, t_file *b)
{
    t_file *swapperVector[4];

    swapperVector[0] = a->prev;
    swapperVector[1] = b->prev;
    swapperVector[2] = a->next;
    swapperVector[3] = b->next;
    if (is_neighbours(a,b))
    {
        a->prev = swapperVector[2];
        b->prev = swapperVector[0];
        a->next = swapperVector[3];
        b->next = swapperVector[1];
    }
    else
    {
        a->prev = swapperVector[1];
        b->prev = swapperVector[0];
        a->next = swapperVector[3];
        b->next = swapperVector[2];
    }
    refresh_pointers(a);
    refresh_pointers(b);
}