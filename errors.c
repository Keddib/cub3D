/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:55:54 by keddib            #+#    #+#             */
/*   Updated: 2020/11/10 00:46:11 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_puterror(char *error)
{
	char *e;

	e = "\033[1;31m(x) Error\n >> \033[2;31m";
	write(1, e, ft_strlen(e));
	write(1, error, ft_strlen(error));
	return (0);
}

int		check_for_file(t_string file_name, t_all *all)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_exit(7, all);
	return (fd);
}

int		ft_exit(int i, t_all *all)
{
	int j;

	j = 0;
	if (i == 0)
	{
		ft_free(all->win.array, all->win.cols);
		free(all->ray);
		free(all->sprite);
		while (j < 5)
		{
			free(all->tex.data[j]);
			free(all->tex.file[j++]);
		}
		mlx_destroy_image(g_mlx.ptr, g_mlx.img);
		mlx_destroy_window(g_mlx.ptr, g_mlx.win);
	}
	else
		ft_puterror(g_messages[i]);
	exit(0);
}

void	check_suffix(char *s, char *cub, t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	i -= 1;
	while (cub[j])
	{
		if (s[i] == cub[j])
			i--;
		else
			ft_exit(9, all);
		j++;
	}
}

void	check_arguments(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (all->param2)
	{
		if (ft_strcmp("--save", all->param2) == 0)
			all->save = 1;
		else
			ft_exit(1, all);
	}
	if (!all->param1 || strlen(all->param1) <= 4)
		ft_exit(1, all);
	check_suffix(all->param1, "buc.", all);
}
