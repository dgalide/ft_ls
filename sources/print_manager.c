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

void 		print_l_mode(t_file *file, t_ls *data)
{
	t_file	*tmp;
	mode_t tmp1;

	tmp = file;
	if (tmp && data)
	{
		define_max_field(&file, data);
		ft_printf("total %d\n", data->byte_blocks);
		while (tmp)
		{
			if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			{
				//ft_printf("max_lnk = {%d} max_uid = {%d} max_gid = {%d} max_size = {%d}\n", data->max_lnk, data->max_uid, data->max_gid, data->max_size);
				tmp1 = (tmp->right_nu & ~S_IFMT);
				ft_printf("%c%c%c%c%c%c%c%c%c%c  %*d %-*s  %-*s  ",
									tmp->first_right,\
									((tmp1 & S_IRUSR) ? 'r' : '-') ,\
									((tmp1 & S_IWUSR) ? 'w' : '-'),\
									((tmp1 & S_IXUSR) ? 'x' : '-'),\
									((tmp1 & S_IRGRP) ? 'r' : '-'),\
									((tmp1 & S_IWGRP) ? 'w' : '-'),\
									((tmp1 & S_IXGRP) ? 'x' : '-'),\
									((tmp1 & S_IROTH) ? 'r' : '-'),\
									((tmp1 & S_IWOTH) ? 'w' : '-'),\
									((tmp1 & S_IXOTH) ? 'x' : '-'),\
				data->max_lnk, tmp->nb_hard_link, data->max_uid, tmp->name_usr,
				data->max_gid, tmp->name_grp);
				if (S_ISCHR(tmp->right_nu) || S_ISBLK(tmp->right_nu))
					ft_printf("%*d,%*d ", data->max_major, tmp->major, data->max_major, tmp->minor);
				else
					ft_printf("%*d ", data->max_major, tmp->minor);
				ft_printf("%s %s\n", time_handler(tmp, data->opt), tmp->name);
			}
			tmp = tmp->next;
		}
	}
}

void		print_manager(t_file *file, t_ls *data)
{

	(data->opt->sr) ? sort_alpha(&file) : 0;
	(data->opt->t && data->opt->sr) ? sort_rdate(&file) : 0;
	(data->opt->t && !(data->opt->sr)) ? sort_date(&file) : 0;
	if (data->opt->l)	
		print_l_mode(file, data);
}