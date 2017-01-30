/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_max_field.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:40:33 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/30 15:40:34 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					check_colon(int value)
{
	int				i;

	i = 0;
	while (value)
	{
		i += 1;
		value /= 10;
	}
	return (i);
}

void				define_max_minor_major(t_file **file, t_ls *data)
{
	t_file			*tmp;
	int				max_col;

	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (check_colon(tmp->major) + check_colon(tmp->minor) + 1 > max_col)
			max_col = check_colon(tmp->major) + check_colon(tmp->minor) + 1;
		tmp = tmp->next;
	}
	data->max_major = max_col;
}

void 				define_max_field_ext(t_file **file, t_ls *data)
{
	t_file			*tmp;
	int				max_col;

	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->name_grp) > max_col)
			max_col = ft_strlen(tmp->name_grp);
		tmp = tmp->next;
	}
	data->max_gid = max_col;
	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->name_usr) > max_col)
			max_col = ft_strlen(tmp->name_usr);
		tmp = tmp->next;	
	}
	data->max_uid = max_col;
	define_max_minor_major(file, data);
}

void 				define_max_field(t_file **file, t_ls *data)
{
	t_file			*tmp;
	int				max_col;

	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (check_colon(tmp->nb_hard_link) > max_col)
			max_col = check_colon(tmp->nb_hard_link);
		tmp = tmp->next;
	}
	data->max_lnk = max_col;
	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (check_colon(tmp->st_size) > max_col)
			max_col = check_colon(tmp->st_size);
		tmp = tmp->next;
	}
	data->max_size = max_col;
	define_max_field_ext(file, data);
}