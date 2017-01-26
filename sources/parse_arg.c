/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:45:10 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/24 17:45:11 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int 				parse(t_ls *ls, char *arg)
{
	if (arg && arg[0] == '-' && !parse_opt(ls, arg))
		return (0);
	else if (arg && arg[0] != '-' && !parse_file(ls, arg))
		return (0);
	else
		return (1);
}