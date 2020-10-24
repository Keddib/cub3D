/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/10/24 22:48:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void *load_images(t_texture *tex)
{
    int fd, i;
    i = 0;
    fd = 0;
    while (i < 4)
    {
        fd = open(tex->file[i], O_RDONLY);
        if (fd == -1)
        {
            ft_exit(2);
        }
        tex->img = mlx_xpm_file_to_image(mlx.pointer, tex->file[i], &tex->width, &tex->height);
        tex->data[i] = (unsigned int *)mlx_get_data_addr(
            tex->img,
            &mlx.bits_per_pixel,
            &mlx.line_length,
            &mlx.endian);
        free(tex->img);
        i++;
    }
    return NULL;
}