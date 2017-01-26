/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:50:21 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/24 16:50:23 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static t_opt	*init_opt(void)
{
	t_opt		*opt;

	if (!(opt = (t_opt *)malloc(sizeof(t_opt))))
		return (NULL);
	opt->l = 0;
	opt->br = 0;
	opt->sr = 0;
	opt->a = 0;
	opt->t = 0;
	return (opt);
}

int			init_data(t_ls *data, char **av, int ac)
{
	int 		i;

	i = 0;
	data->arg = NULL;
	data->opt = init_opt();
	while (++i < ac)
		if (!parse(data, av[i]))
			return (0);
	return (1);
}