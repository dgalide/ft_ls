/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_max_field.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:40:33 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/30 21:28:33 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				define_max_minor_major(t_file **file, t_ls *data)
{
	t_file			*tmp;
	int				max_col;

	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			if (check_colon(tmp->major) + check_colon(tmp->minor) + 1 > max_col)
				max_col = check_colon(tmp->major) + check_colon(tmp->minor) + 1;
		tmp = tmp->next;
	}
	data->max_major = max_col;
}

void				define_max_field_ext(t_file **file, t_ls *data)
{
	t_file			*tmp;
	int				max_col;

	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			if ((int)ft_strlen(tmp->name_grp) > max_col)
				max_col = ft_strlen(tmp->name_grp);
		tmp = tmp->next;
	}
	data->max_gid = max_col;
	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			if ((int)ft_strlen(tmp->name_usr) > max_col)
				max_col = ft_strlen(tmp->name_usr);
		tmp = tmp->next;
	}
	data->max_uid = max_col;
	define_max_minor_major(file, data);
}

void				define_max_filename(t_file **file, t_ls *data)
{
	t_file			*tmp;
	int				max;

	tmp = *file;
	max = 0;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->name) > max && (tmp->name[0] != '.' ||
			(tmp->name[0] == '.' && data->opt->a)))
			max = ft_strlen(tmp->name);
		tmp = tmp->next;
	}
	data->max_name = max;
}

void				define_max_field(t_file **file, t_ls *data)
{
	t_file			*tmp;
	int				max_col;

	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			if (check_colon(tmp->nb_hard_link) > max_col)
				max_col = check_colon(tmp->nb_hard_link);
		tmp = tmp->next;
	}
	data->max_lnk = max_col;
	tmp = *file;
	max_col = 0;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			if (check_colon(tmp->st_size) > max_col)
				max_col = check_colon(tmp->st_size);
		tmp = tmp->next;
	}
	data->max_size = max_col;
	define_max_field_ext(file, data);
	define_max_filename(file, data);
}
