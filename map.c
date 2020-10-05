/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:49:59 by keddib            #+#    #+#             */
/*   Updated: 2020/10/05 18:29:55 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void ft_square(int x, int y, int color)
{
  int p, p1;
  p1 = y;
  p = x;

  while (y <= p1 + window.tile_size)
  {
    x = p;
    while (x <= p + window.tile_size)
    {
      my_mlx_pixel_put(&mlx, x, y, color);
      x++;
    }
    y++;
  }
}

int is_this_wall(float x, float y)
{
  if (x < 0 || x > window.width || y < 0 || y > window.height)
    return 1;
  int index_x;
  int index_y;
  index_x = floor(x / window.tile_size);
  index_y = floor(y / window.tile_size);
  if (index_y >= window.num_map_cols || index_x >= window.num_map_rows)
    return 1;

  if (window.array[index_y][index_x] == '1')
    return 1;
  return 0;
}

void map_render()
{
  int i = 0;
  int j = 0;
  int tile_x = 0;
  int tile_y = 0;
  int color;

  while (i < window.num_map_cols)
  {
    j = 0;
    while (j < window.num_map_rows)
    {
      tile_x = j * window.tile_size;
      tile_y = i * window.tile_size;
      color = window.array[i][j] == '1' ? 0xfff : 0x000;
      ft_square(tile_x, tile_y, color);
      j++;
    }
    i++;
  }
}
