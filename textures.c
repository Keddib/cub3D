/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 05:47:51 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
		all->tex.img = mlx_xpm_file_to_image(g_mlx.ptr,
				all->tex.file[i], &all->tex.width, &all->tex.height);
		all->tex.data[i] = (unsigned int *)mlx_get_data_addr(
				all->tex.img,
				&g_mlx.bpp,
				&g_mlx.line_n,
				&g_mlx.endian);
		free(all->tex.img);
		i++;
	}
	return (NULL);
}
