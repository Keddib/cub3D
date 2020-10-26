/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:59:36 by keddib            #+#    #+#             */
/*   Updated: 2020/10/26 01:33:05 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void update_player()
{
  float new_player_x;
  float new_player_y;
  float move_step;
  float side_step;
  float nex_half = g_window.half_win + (g_window.look * 5);

  if (nex_half > (g_window.height / 4) && nex_half < ((g_window.height / 4) * 3))
    g_window.half_win += (g_window.look * 5);
  g_player.rotation_angle += g_player.turn_direction * TURN_SPEED;
  move_step = g_player.walk_direction * WALK_SPEED;
  new_player_x = g_player.x + cos(g_player.rotation_angle) * move_step;
  new_player_y = g_player.y + sin(g_player.rotation_angle) * move_step;
  side_step = g_player.side_direction * WALK_SPEED;
  new_player_x += cos(g_player.rotation_angle + (90 * RADIUN)) * side_step;
  new_player_y += sin(g_player.rotation_angle + (90 * RADIUN)) * side_step;
  if (!is_this_wall(new_player_x, new_player_y))
  {
    g_player.x = new_player_x;
    g_player.y = new_player_y;
  }
}

int is_this_wall(float x, float y)
{
  if (x < 0 || x > (g_window.rows * TILE_SIZE) || y < 0 || y > (g_window.cols * TILE_SIZE))
    return 1;
  int index_x;
  int index_y;
  index_x = floor(x / TILE_SIZE);
  index_y = floor(y / TILE_SIZE);
  if (index_y >= g_window.cols || index_x >= g_window.rows)
    return 1;
  if (g_window.array[index_y][index_x] == '1')
    return 1;
  return 0;
}

int ft_puterror(char *error)
{
  char *e;
  e = "\033[1;31m(x) Error\n >> \033[0;31m";
  write(1, e, ft_strlen(e));
  write(1, error, ft_strlen(error));
  return 0;
}

int ft_exit(int i)
{
  if (i == 0)
  {
    ft_free(g_window.array, g_window.cols);
    mlx_destroy_image(mlx.pointer, mlx.image);
    mlx_destroy_window(mlx.pointer, mlx.window);
    mlx.image = NULL;
    mlx.window = NULL;
    mlx.pointer = NULL;
  }
  else if (i == 1)
    ft_puterror("ERROR\nFILE NOT FOUND\n");
  // ft_putstr("ERROR\nFILE NOT FOUND\n");
  else if (i == 2)
    ft_puterror("Somthing is Missing Check Your File\n");
  else if (i == 3)
    ft_putstr("ERROR\nDUPP PLAYER\n");
  exit(0);
}

int ft_strcmp(const char *s1, const char *s2)
{
  size_t i;
  unsigned char *s;
  unsigned char *z;

  s = (unsigned char *)s1;
  z = (unsigned char *)s2;
  if (!s1 && !s2)
    return (0);
  i = 0;
  while (s[i] != '\0' || z[i] != '\0')
  {
    if (s[i] - z[i] != 0)
      return (s[i] - z[i]);
    i++;
  }
  return (*s1 - *s2);
}