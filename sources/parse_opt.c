/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:49:33 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/30 21:11:35 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			add_opt(t_ls *ls, char c)
{
	if (c == 'l')
		ls->opt->l = 1;
	else if (c == 'R')
		ls->opt->br = 1;
	else if (c == 'r')
		ls->opt->sr = 1;
	else if (c == 'a')
		ls->opt->a = 1;
	else if (c == 't')
		ls->opt->t = 1;
	else if (c == 'T')
		ls->opt->bt = 1;
}

static int 			is_valid_opt(char c)
{
	if (c == 'l' || c == 'R' || c == 'r' || c == 'a' || c == 't' || c == 'T')
		return (1);
	else
		return (0);
}

int 				parse_opt(t_ls *ls, char *str)
{
	t_opt		*tmp;
	char		*tab;
	int 		i;

	tab = NULL;
	tmp = ls->opt;
	i = 0;
	while (str && str[++i])
	{
		if (!is_valid_opt(str[i]))
			return (0);
		add_opt(ls, str[i]);
	}
	return (1);
}