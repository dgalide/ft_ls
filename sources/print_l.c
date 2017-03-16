/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 01:56:06 by dgalide           #+#    #+#             */
/*   Updated: 2017/03/13 01:56:08 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			print_right(t_file *file)
{
	mode_t		tmp1;

	tmp1 = (file->right_nu & ~S_IFMT);
	ft_printf("%c%c%c%c%c%c%c%c%c%c  ", file->first_right,\
									((tmp1 & S_IRUSR) ? 'r' : '-'),\
									((tmp1 & S_IWUSR) ? 'w' : '-'),\
									((tmp1 & S_IXUSR) ? 'x' : '-'),\
									((tmp1 & S_IRGRP) ? 'r' : '-'),\
									((tmp1 & S_IWGRP) ? 'w' : '-'),\
									((tmp1 & S_IXGRP) ? 'x' : '-'),\
									((tmp1 & S_IROTH) ? 'r' : '-'),\
									((tmp1 & S_IWOTH) ? 'w' : '-'),\
									((tmp1 & S_IXOTH) ? 'x' : '-'));
}

void			print_l_mode_extend(t_file **file, t_ls *data, int bool_major)
{
	print_right((*file));
	ft_printf("%*d ", data->max_lnk, (*file)->nb_hard_link);
	(!(data->opt->sg)) ? ft_printf("%-*s  ", data->max_uid, (*file)->name_usr) : 0;
	ft_printf("%-*s ", data->max_gid, (*file)->name_grp);
	if (S_ISCHR((*file)->right_nu) || S_ISBLK((*file)->right_nu))
		ft_printf("%*d,%*d ", data->max_major, (*file)->major,
			data->max_major, (*file)->minor);
	else
		ft_printf("%*d ", ((bool_major) ? data->max_major * 2 + 1 :
			data->max_major), (*file)->minor);
	ft_printf("%s %s", time_handler((*file), data->opt), (*file)->name);
	((*file)->first_right == 'l') ? ft_printf(" -> %s\n", (*file)->sym_link) :
	ft_printf("\n");
	if (!(*file)->next && data->opt->br)
		ft_putchar('\n');
}

void			print_l_mode(t_file **file, t_ls *data)
{
	t_file		*tmp;
	static int	br;
	int			bool_major;

	tmp = *file;
	bool_major = check_major(*file);
	set_byte_blocks(file, data);
	if (tmp && data)
	{
		(br++ != 0) ? ft_printf("%s:\n", tmp->parent_path) : 0;
		ft_printf("total %d\n", tmp->byte_blocks);
		while (tmp)
		{
			if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
				print_l_mode_extend(&tmp, data, bool_major);
			tmp = tmp->next;
		}
	}
}
