/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 20:07:06 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/30 21:36:30 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*time_handler(t_file *file, t_opt *opt)
{
	char *tmp;
	char *tmp2;

	if (opt->bt)
		tmp = ft_strsub(file->mtime, 4, 20);
	else if (time(0) - file->time <= 15724800)
		tmp = ft_strsub(file->mtime, 4, 12);
	else
	{
		tmp = ft_strsub(file->mtime, 4, 7);
		tmp2 = ft_strsub(file->mtime, 19, 5);
		tmp = ft_strjoin_free(&tmp, &tmp2, 1, 1);
	}
	return (tmp);
}

int			check_major(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (tmp)
	{
		if (S_ISCHR(tmp->right_nu) || S_ISBLK(tmp->right_nu))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		print_classic_mode(t_file *file, t_ls *data)
{
	t_file	*tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}

void		print_manager(t_file *file, t_ls *data)
{
	sort_alpha_rev(&file);
	(data->opt->sr) ? sort_alpha(&file) : 0;
	(data->opt->t && data->opt->sr) ? sort_rdate(&file) : 0;
	(data->opt->t && !(data->opt->sr)) ? sort_date(&file) : 0;
	define_max_field(&file, data);
	if (data->opt->l || data->opt->sg)
		print_l_mode(file, data);
	else
		print_classic_mode(file, data);
}
