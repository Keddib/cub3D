/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:45:37 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 06:28:34 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		check_char(char c, t_all *all)
{
	if (c != '1' && c != '0' && c != '2' && c != 'W' &&
		c != 'N' && c != 'S' && c != 'E' && c != ' ')
		ft_exit(14, all);
	if ((c == 'N' || c == 'W' || c == 'S' || c == 'E') && all->win.chr == 1)
		ft_exit(13, all);
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		all->win.chr = 1;
}

static void		check_array(int j, int i, t_all *all)
{
	if (all->win.array[j][i] == 'N' || all->win.array[j][i] == 'W' ||
		all->win.array[j][i] == 'E' || all->win.array[j][i] == 'S')
	{
		all->fpp.x = (i * TILE_SIZE) + (TILE_SIZE / 2);
		all->fpp.y = (j * TILE_SIZE) + (TILE_SIZE / 2);
		if (all->win.array[j][i] == 'S')
			all->fpp.rotation_angle = M_PI / 2;
		else if (all->win.array[j][i] == 'N')
			all->fpp.rotation_angle = M_PI * 1.5;
		else if (all->win.array[j][i] == 'E')
			all->fpp.rotation_angle = M_PI * 0;
		else if (all->win.array[j][i] == 'W')
			all->fpp.rotation_angle = M_PI * 1;
	}
	if (all->win.array[j][i] == '2')
		all->num_sprt += 1;
	if (j == 0 || (j == all->win.cols - 1))
		ft_exit(6, all);
	else if (i == (all->win.rows - 1))
		ft_exit(6, all);
	else if (all->win.array[j + 1][i] == ' ' || all->win.array[j - 1][i] == ' ')
		ft_exit(6, all);
	else if (all->win.array[j][i + 1] == ' ' || all->win.array[j][i - 1] == ' ')
		ft_exit(6, all);
}

static int		check_error(t_all *all)
{
	int i;
	int j;

	j = 0;
	all->win.chr = 0;
	while (all->win.array[j])
	{
		i = 0;
		while (all->win.array[j][i])
		{
			if (all->win.array[j][i] == '0' || all->win.array[j][i] == 'N' ||
				all->win.array[j][i] == 'W' || all->win.array[j][i] == '2' ||
				all->win.array[j][i] == 'E' || all->win.array[j][i] == 'S')
				check_array(j, i, all);
			check_char(all->win.array[j][i], all);
			i++;
		}
		j++;
	}
	return (0);
}

void			check_map(char *line, char **strmap, t_all *all)
{
	int len;

	len = 0;
	len = ft_strlen(line);
	if (line[0] == '\n' || all->file.counter != 8)
	{
		ft_exit(12, all);
		free(line);
	}
	else if (line[0] == '0' || line[len - 2] == '0')
	{
		ft_exit(10, all);
		free(line);
	}
	all->win.rows = (len > all->win.rows) ? len - 1 : all->win.rows;
	*strmap = ft_strjoin(*strmap, line, 0);
}

void			read_file(char *path, t_all *all)
{
	int		fd;
	char	*line;
	char	*strmap;

	strmap = NULL;
	fd = check_for_file(path, all);
	while (get_next_line(fd, &line))
	{
		if (all->file.map_found == 0)
			check_line(line, all);
		if (all->file.map_found == 1)
			check_map(line, &strmap, all);
		free(line);
	}
	if (all->file.map_found == 0)
		ft_exit(6, all);
	strmap = ft_strjoin(strmap, line, 0);
	free(line);
	all->win.array = ft_split(strmap, '\n', &all->win.cols);
	free(strmap);
	check_error(all);
	if (all->win.chr == 0)
		ft_exit(11, all);
}
