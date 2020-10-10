/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:47:59 by keddib            #+#    #+#             */
/*   Updated: 2020/10/10 20:51:14 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void ft_exit(int i)
{
  if (i == 0)
  {
    ft_free(window.array, window.num_map_cols);
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
