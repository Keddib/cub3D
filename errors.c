/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:55:54 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 06:48:40 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_errors(void)
{
	g_messages[0] = "Invalid file name!";
	g_messages[1] = "Added info in an element";
	g_messages[2] = "Duplicate Texture";
	g_messages[3] = "Duplicate Color";
	g_messages[4] = "Error in Resolution";
	g_messages[5] = "Stop Idiot! You have reached the range of g_screen";
	g_messages[6] = "Invalid Map";
	g_messages[7] = "NO SUCH FILE OR DIRECTORY";
	g_messages[8] = "Allocation Failed";
	g_messages[9] = "STOP! you need XPM file";
	g_messages[10] = "INVALID MAP LINE";
	g_messages[11] = "NO PLAYER FOUNDED";
	g_messages[12] = "NEW LINE IN MAP";
	g_messages[13] = "DUPLICATE_PLAYER";
	g_messages[14] = "INVALID CHARCATER";
	g_messages[15] = "INVALID COLORS";
	g_messages[16] = "DUPLICATE_SPRITE";
	g_messages[17] = "ARGUMENTS ARE MORE OR LESS";
}

int		ft_puterror(char *error)
{
	char *e;

	e = "\033[1;31m(x) Error\n >> \033[0;31m";
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
