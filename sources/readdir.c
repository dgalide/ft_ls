/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 22:46:24 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/24 22:46:25 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int 				is_current_dir(char *name)
{
	char			*tmp;

	tmp = NULL;
	if (name && ft_strlen(name) == 1 && name[0] == '.')
		return (1);
	else if (name && ft_strlen(name) == 2 && name[0] == '.' && name[1] == '.')
		return (1);
	else
		return (0);
}
