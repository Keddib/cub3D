/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 00:40:01 by keddib            #+#    #+#             */
/*   Updated: 2020/10/04 19:07:16 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int key_pressed(int key, void *param)
{

    if (key == 65307)
        ft_exit(0);
    if (key == 119)
        player.walk_direction = +1;
    else if (key == 115)
        player.walk_direction = -1;
    else if (key == 100)
        player.side_direction = +1;
    else if (key == 97)
        player.side_direction = -1;
    else if (key == 65363)
        player.turn_direction = +1;
    else if (key == 65361)
        player.turn_direction = -1;
    update_player();
    return 0;
}

int key_released(int key, void *param)
{
    if (key == 119)
        player.walk_direction = 0;
    else if (key == 115)
        player.walk_direction = 0;
    else if (key == 100)
        player.side_direction = 0;
    else if (key == 97)
        player.side_direction = 0;
    else if (key == 65363)
        player.turn_direction = 0;
    else if (key == 65361)
        player.turn_direction = 0;
    update_player();
    return 0;
}
