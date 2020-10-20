/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:59:36 by keddib            #+#    #+#             */
/*   Updated: 2020/10/20 11:07:24 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void update_player()
{
  float new_player_x;
  float new_player_y;
  float move_step;
  float side_step;

  player.rotation_angle += player.turn_direction * TURN_SPEED;
  move_step = player.walk_direction * WALK_SPEED;
  new_player_x = player.x + cos(player.rotation_angle) * move_step;
  new_player_y = player.y + sin(player.rotation_angle) * move_step;
  side_step = player.side_direction * WALK_SPEED;
  new_player_x += cos(player.rotation_angle + (90 * RADIUN)) * side_step;
  new_player_y += sin(player.rotation_angle + (90 * RADIUN)) * side_step;
  if (!is_this_wall(new_player_x, new_player_y))
  {
    player.x = new_player_x;
    player.y = new_player_y;
  }
}

int is_this_wall(float x, float y)
{
  if (x < 0 || x > (window.num_rows * TILE_SIZE) || y < 0 || y > (window.num_cols * TILE_SIZE))
    return 1;
  int index_x;
  int index_y;
  index_x = floor(x / TILE_SIZE);
  index_y = floor(y / TILE_SIZE);
  if (index_y >= window.num_cols || index_x >= window.num_rows)
    return 1;
  if (window.array[index_y][index_x] == '1')
    return 1;
  return 0;
}

void ft_exit(int i)
{
  if (i == 0)
  {
    ft_free(window.array, window.num_cols);
    mlx_destroy_window(mlx.pointer, mlx.window);
    free(mlx.image);
    mlx.image = NULL;
    mlx.window = NULL;
    mlx.pointer = NULL;
  }
  else if (i == 1)
    ft_putstr("ERROR\nFILE NOT FOUND\n");
  else if (i == 2)
    ft_putstr("ERROR\nMAP INVALIDb\n");
  else if (i == 3)
    ft_putstr("ERROR\nDUPP PLAYER\n");
  exit(0);
}