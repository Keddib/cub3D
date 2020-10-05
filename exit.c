/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:47:59 by keddib            #+#    #+#             */
/*   Updated: 2020/09/24 03:10:36 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void ft_exit(int i)
{
  if (i == 0)
  {
    mlx_destroy_window(mlx.pointer, mlx.window);
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
