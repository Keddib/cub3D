/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:47:18 by keddib            #+#    #+#             */
/*   Updated: 2020/10/25 22:27:09 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int str_containe(char **s, int n)
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

int change_rgb(char *s)
{
    char **lines;
    int cols;
    int color;
    lines = ft_split(s, ',', &cols);
    if (cols != 3)
    {
        ft_free(lines, cols);
        ft_exit(2);
    }
    color = 65536 * ft_atoi(lines[0]) + 256 * ft_atoi(lines[1]);
    color += ft_atoi(lines[2]);
    ft_free(lines, cols);
    return (color);
}

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