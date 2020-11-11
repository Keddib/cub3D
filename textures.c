/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/11/10 00:00:31 by keddib           ###   ########.fr       */
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

int		which_texture(t_all *all, int x)
{
	int wich_tex;

	wich_tex = 0;
	if (all->ray[x].was_hit_vertical && all->ray[x].facingright)
		wich_tex = 3;
	else if (all->ray[x].was_hit_vertical && all->ray[x].facingleft)
		wich_tex = 2;
	else if (all->ray[x].was_hit_vertical == 0 && all->ray[x].facingdown)
		wich_tex = 1;
	return (wich_tex);
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
		all->tex.img[i] = mlx_xpm_file_to_image(g_mlx.ptr,
				all->tex.file[i], &all->tex.width, &all->tex.height);
		all->tex.data[i] = (unsigned int *)mlx_get_data_addr(
				all->tex.img[i],
				&g_mlx.bpp,
				&g_mlx.line_n,
				&g_mlx.endian);
		// mlx_destroy_image(g_mlx.ptr, all->tex.img);
		// free(all->tex.img);
		i++;
	}
	return (NULL);
}
