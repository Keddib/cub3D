/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/10/20 12:27:17 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
t_texture *load_images()
{
    t_texture *tex;

    tex = malloc(sizeof(t_texture) * 4);
    tex[0].file = "tpics/colorstone.xpm";
    tex[1].file = "tpics/greystone.xpm";
    tex[2].file = "tpics/mossy.xpm";
    tex[3].file = "tpics/redbrick.xpm";

    for (int i = 0; i < 4; i++)
    {
        tex[i].img = mlx_xpm_file_to_image(mlx.pointer, tex[i].file, &tex[i].width, &tex[i].height);
        tex[i].data = (unsigned int *)mlx_get_data_addr(
            tex[i].img,
            &mlx.bits_per_pixel,
            &mlx.line_length,
            &mlx.endian);
    }
    return tex;
}