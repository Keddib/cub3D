/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:25:11 by keddib            #+#    #+#             */
/*   Updated: 2020/10/24 23:34:24 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float normalizeAngle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
    {
        angle = TWO_PI + angle;
    }
    return angle;
}
float distance_between_points(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void cast_ray(float ray_angle, t_ray *ray)
{
    t_incept incept;
    ray->ray_angle = normalizeAngle(ray_angle);
    ray->ray_facingdown = ray->ray_angle > 0 && ray->ray_angle < PI;
    ray->ray_facingup = !ray->ray_facingdown;
    ray->ray_facingright = ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI;
    ray->ray_facingleft = !ray->ray_facingright;
    get_horizontal(ray, &incept);
    get_vertical(ray, &incept);
    // Calculate both horizontal and vertical hit distances and choose the smallest one
    calc_distances(&incept);
    if (incept.vert_distance < incept.horz_distance)
    {
        ray->distance = incept.vert_distance;
        ray->wall_hit_x = incept.vert_x;
        ray->wall_hit_y = incept.vert_y;
        ray->was_hit_vertical = 1;
    }
    else
    {
        ray->distance = incept.horz_distance;
        ray->wall_hit_x = incept.horz_x;
        ray->wall_hit_y = incept.horz_y;
        ray->was_hit_vertical = 0;
    }
}

void cast_all_rays(t_texture *tex)
{
    int i;
    float ray_angle;
    t_ray ray;

    i = 0;
    ray_angle = player.rotation_angle - (FOV_ANGLE / 2);
    while (i < window.width)

    {
        cast_ray(ray_angle, &ray);
        render_3d_projection(ray, tex, i);
        ray_angle += (FOV_ANGLE / window.width);
        i++;
    }
}