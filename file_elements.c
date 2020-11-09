/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 06:13:01 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 06:37:41 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_element(char **splited_line, t_all *all, int i)
{
	if (i == 5 || i == 6)
	{
		if (all->tex.color[i - 5] != 0)
			ft_exit(3, all);
		all->tex.color[i - 5] = change_rgb(splited_line[1], all);
		all->file.counter += 1;
	}
	else
	{
		if (all->tex.file[i] != NULL)
			ft_exit(2, all);
		all->tex.file[i] = ft_path(splited_line[1]);
		check_for_file(all->tex.file[i], all);
		check_suffix(all->tex.file[i], "mpx.", all);
		all->file.counter += 1;
	}
}

void	check_resolution(t_all *all, int cols, char **lines)
{
	//todo // check resolution if bigger than any machine
	// int width;
	// int height;
	if (cols != 3 || all->file.res == 1)
		ft_exit(4, all);
	all->win.width = ft_atoi(lines[1]);
	all->win.height = ft_atoi(lines[2]);
	all->file.counter += 1;
	all->file.res = 1;
	// mlx_get_screen_size(g_mlx.ptr, &width, &height);
	// // printf("x = %d| y == %d\n", width, height);
	// ft_exit(1, all);
}

int		str_ismap(char **s, int n)
{
	int i;
	int j;
	int yes;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == '1' || s[i][j] == ' ' || s[i][j] == '\n')
				yes = 1;
			else
				return (0);
			j++;
		}
		i++;
	}
	return (yes);
}

void	check_line2(char **splited_line, int cols, t_all *all)
{
	if (ft_strcmp(splited_line[0], "S") == 0)
		check_element(splited_line, all, 4);
	else if (ft_strcmp(splited_line[0], "C") == 0)
		check_element(splited_line, all, 5);
	else if (ft_strcmp(splited_line[0], "F") == 0)
		check_element(splited_line, all, 6);
	else if (str_ismap(splited_line, cols))
		all->file.map_found = 1;
	else
	{
		ft_free(splited_line, cols);
		ft_exit(10, all);
	}
}

void	check_line(char *line, t_all *all)
{
	char	**splited_line;
	int		cols;

	if (line[0] == '\n')
		return ;
	splited_line = ft_split(line, ' ', &cols);
	if (ft_strcmp(splited_line[0], "R") == 0)
		check_resolution(all, cols, splited_line);
	else if (cols != 2 && !str_ismap(splited_line, cols))
		ft_exit(1, all);
	else if (ft_strcmp(splited_line[0], "NO") == 0)
		check_element(splited_line, all, 0);
	else if (ft_strcmp(splited_line[0], "SO") == 0)
		check_element(splited_line, all, 1);
	else if (ft_strcmp(splited_line[0], "WE") == 0)
		check_element(splited_line, all, 2);
	else if (ft_strcmp(splited_line[0], "EA") == 0)
		check_element(splited_line, all, 3);
	else
		check_line2(splited_line, cols, all);
	ft_free(splited_line, cols);
}
