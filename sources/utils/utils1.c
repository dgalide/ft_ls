/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 04:10:53 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/13 04:10:58 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

char		*format_path(char *curr_path, char *name_file)
{
	char	*tmp;

	tmp = NULL;
	if (curr_path && name_file)
	{
		tmp = ft_strjoin(curr_path,
			(curr_path[ft_strlen(curr_path) - 1] != '/') ? "/" : NULL);
		return (ft_strjoin_free(&tmp, &name_file, 1, 0));
	}
	else
		return (NULL);
}