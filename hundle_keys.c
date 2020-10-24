/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 00:40:01 by keddib            #+#    #+#             */
/*   Updated: 2020/10/24 23:33:12 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int key_pressed(int key, void *param)
{
    param = NULL;
    if (key == 53)
        ft_exit(0);
    if (key == 13)
        player.walk_direction = +1;
    else if (key == 1)
        player.walk_direction = -1;
    else if (key == 2)
        player.side_direction = +1;
    else if (key == 0)
        player.side_direction = -1;
    else if (key == 124)
        player.turn_direction = +1;
    else if (key == 123)
        player.turn_direction = -1;
    return 0;
}

int key_released(int key, void *param)
{
    param = NULL;
    if (key == 13 || key == 1)
        player.walk_direction = 0;
    else if (key == 2 || key == 0)
        player.side_direction = 0;
    else if (key == 124 || key == 123)
        player.turn_direction = 0;
    return 0;
}
