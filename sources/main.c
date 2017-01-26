/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:29:24 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/24 16:29:27 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			print_data(t_ls *data)
{
	t_arg		*arg;

	arg = data->arg;
	while (arg)
	{
		arg = arg->next;
		ft_putendl(arg->name_dir);
	}
	ft_printf("l = {%d} , R = {%d} , r = {%d} , a = {%d} , t = {%d}\n", data->opt->l, data->opt->br, data->opt->sr, data->opt->a, data->opt->t);
}

int				main(int ac, char **av)
{
	t_ls		data;

	if (!init_data(&data, av, ac))
		return (0);
	ls_process(&data);
	//print_data(&data);
}