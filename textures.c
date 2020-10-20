/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/10/20 17:49:09 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void *load_images(t_texture *tex)
{
    int fd, i;
    i = 0;
    tex->file[0] = "tpics/colorstone.xpm";
    tex->file[1] = "tpics/greystone.xpm";
    tex->file[2] = "tpics/mossy.xpm";
    tex->file[3] = "tpics/redbrick.xpm";
    fd = 0;
    while (i < 4)
    {
        fd = open(tex->file[i], O_RDONLY);
        if (fd == -1)
            ft_exit(0);
        tex->img = mlx_xpm_file_to_image(mlx.pointer, tex->file[i], &tex->width, &tex->height);
        tex->data[i] = (unsigned int *)mlx_get_data_addr(
            tex->img,
            &mlx.bits_per_pixel,
            &mlx.line_length,
            &mlx.endian);
        free(tex->img);
        // for (int x = 0; x < 64 * 64; x++)
        //     printf("[%d]%d\n", x, tex->data[i][x]);
        i++;
    }
    return NULL;
}