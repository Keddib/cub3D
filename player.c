/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 02:19:08 by keddib            #+#    #+#             */
/*   Updated: 2020/10/05 03:34:51 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** here I will setup my player and render it, the update also will be here
*/

void setup_player()
{
    //player.x = window.width / 2;
    //player.y = window.height / 2;
    //player.radius = 10;
    //player.rotation_angle = M_PI / 2;
    player.walk_direction = 0;
    player.side_direction = 0;
    player.turn_direction = 0;
    player.move_speed = 0;
}

void update_player()
{
    float new_player_x;
    float new_player_y;
    float move_step;
    float side_step;

    	player.rotation_angle += player.turn_direction * TURN_SPEED;
        move_step = player.walk_direction * (WALK_SPEED + player.move_speed);
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

void draw_line(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps;
    float incx;
    float incy;
    float i1 = x1;
    float j1 = y1;

    steps = (fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy));
    incx = dx / steps;
    incy = dy / steps;
    while (steps > 0)
    {
        my_mlx_pixel_put(&mlx, x1, y1, 0xffff00);
        i1 += incx;
        j1 += incy;
        x1 = i1;
        y1 = j1;
        steps--;
    }
}

void render_player(int x, int y)
{
    my_mlx_pixel_put(&mlx, x, y, 0xffffff);
    draw_line(x,
              y,
              x + (cos(player.rotation_angle) * 15),
              y + (sin(player.rotation_angle) * 15));
}
