/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 04:13:44 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/13 04:13:46 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		error_handler(char *path, t_ls *data, int bool_exit)
{
	(void)data;
	ft_printf("ls: %s: %s\n", path, strerror(errno));
	if (bool_exit)
		exit(3);
}