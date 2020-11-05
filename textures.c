/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/11/02 02:33:05 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		str_containe(char **s, int n)
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

int		change_rgb(char *s, t_all *all)
{
	char	**lines;
	int		cols;
	int		color;

	lines = ft_split(s, ',', &cols);
	if (cols != 3)
	{
		ft_free(lines, cols);
		ft_exit(2, all);
	}
	color = 65536 * ft_atoi(lines[0]) + 256 * ft_atoi(lines[1]);
	color += ft_atoi(lines[2]);
	ft_free(lines, cols);
	return (color);
}

void	*load_images(t_all *all)
{
	int fd;
	int i;

	i = 0;
	fd = 0;
	while (i < 5)
	{
		fd = open(all->tex.file[i], O_RDONLY);
		if (fd == -1)
			ft_exit(2, all);
		all->tex.img = mlx_xpm_file_to_image(all->mlx.pointer,
				all->tex.file[i], &all->tex.width, &all->tex.height);
		all->tex.data[i] = (unsigned int *)mlx_get_data_addr(
				all->tex.img,
				&all->mlx.bits_per_pixel,
				&all->mlx.line_length,
				&all->mlx.endian);
		free(all->tex.img);
		i++;
	}
	return (NULL);
}
