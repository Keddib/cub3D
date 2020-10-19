/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/10/19 20:46:24 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
unsigned int *load_images()
{
    int width;
    int height;
    char *filename = "tpics/colorstone.xpm";
    void *texture;
    unsigned int *img_data;
    texture = mlx_xpm_file_to_image(mlx.pointer, filename, &width, &height);
    img_data = (unsigned int *)mlx_get_data_addr(texture, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
    return img_data;
}