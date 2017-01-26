/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 20:07:06 by dgalide           #+#    #+#             */
/*   Updated: 2017/01/26 20:07:11 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void 		print_l_mode(t_file *file, t_ls *data)
{
	t_file	*tmp;

	tmp = file;
	ft_putendl("-- PRINT_L --");
	if (tmp && data)
	{
		while (tmp)
		{
			tmp->right_nu = (tmp->right_nu & ~S_IFMT);
			ft_printf("%c%c%c%c%c%c%c%c%c%c  %d %s %s %s\n", ((tmp->is_dir) ? 'd' : '-'),\
								((tmp->right_nu & S_IRUSR) ? 'r' : '-') ,\
								((tmp->right_nu & S_IWUSR) ? 'w' : '-'),\
								((tmp->right_nu & S_IXUSR) ? 'x' : '-'),\
								((tmp->right_nu & S_IRGRP) ? 'r' : '-'),\
								((tmp->right_nu & S_IWGRP) ? 'w' : '-'),\
								((tmp->right_nu & S_IXGRP) ? 'x' : '-'),\
								((tmp->right_nu & S_IROTH) ? 'r' : '-'),\
								((tmp->right_nu & S_IWOTH) ? 'w' : '-'),\
								((tmp->right_nu & S_IXOTH) ? 'x' : '-'),\
								tmp->nb_hard_link, tmp->name_usr, tmp->name_grp, tmp->name);
			tmp = tmp->next;
		}
	}
}

void		print_manager(t_file *file, t_ls *data)
{
	if (data->opt->l)
		print_l_mode(file, data);
}