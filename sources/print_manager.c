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

void		print_classic_mode(t_file **file, t_ls *data)
{
	t_file	*tmp;
	static int br;

	tmp = *file;
	(br++ != 0) ? ft_printf("%s:\n", tmp->parent_path) : 0;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && data->opt->a))
			ft_printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	if (data->opt->br)
		ft_printf("\n");
}

void		print_manager(t_file **file, t_ls *data)
{
	if (*file)
	{
		sort_alpha_rev(file);
		(data->opt->sr) ? sort_alpha(file) : 0;
		(data->opt->t && data->opt->sr) ? sort_rdate(file) : 0;
		(data->opt->t && !(data->opt->sr)) ? sort_date(file) : 0;
		define_max_field(file, data);
		if (data->opt->l || data->opt->sg)
			print_l_mode(file, data);
		else
			print_classic_mode(file, data);
	}
}
