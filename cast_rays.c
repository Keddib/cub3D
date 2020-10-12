/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:25:11 by keddib            #+#    #+#             */
/*   Updated: 2020/10/12 12:40:30 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int is_inside_grid(float x, float y)
{
    if (x >= 0 && x <= window.width && y >= 0 && y <= window.height)
        return 1;
    return 0;
}

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

int cast_ray(float ray_angle, int i)
{
    ray_angle = normalizeAngle(ray_angle);

    int isRayFacingDown = ray_angle > 0 && ray_angle < PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = 0;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(player.y / window.tile_size) * window.tile_size;
    yintercept += isRayFacingDown ? window.tile_size : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = player.x + (yintercept - player.y) / tan(ray_angle);

    // Calculate the increment xstep and ystep
    ystep = window.tile_size;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = window.tile_size / tan(ray_angle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= window.width && nextHorzTouchY >= 0 && nextHorzTouchY <= window.height)
    {
        float yToCheck;
        float xToCheck = nextHorzTouchX;
        if (isRayFacingDown)
            yToCheck = nextHorzTouchY + 1;
        else
            yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if (is_this_wall(xToCheck, yToCheck))
        {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            foundHorzWallHit = 1;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = 0;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(player.x / window.tile_size) * window.tile_size;
    xintercept += isRayFacingRight ? window.tile_size : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = player.y + (xintercept - player.x) * tan(ray_angle);

    // Calculate the increment xstep and ystep
    xstep = window.tile_size;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = window.tile_size * tan(ray_angle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= window.width && nextVertTouchY >= 0 && nextVertTouchY <= window.height)
    {
        float xToCheck;
        if (isRayFacingRight)
            xToCheck = nextVertTouchX + 1;
        else
            xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;

        if (is_this_wall(xToCheck, yToCheck))
        {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            foundVertWallHit = 1;
            break;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    float horzHitDistance = foundHorzWallHit
                                ? distance_between_points(player.x, player.y, horzWallHitX, horzWallHitY)
                                : (float)INT_MAX;
    float vertHitDistance = foundVertWallHit
                                ? distance_between_points(player.x, player.y, vertWallHitX, vertWallHitY)
                                : (float)INT_MAX;
    if (vertHitDistance < horzHitDistance)
    {
        rays[i].distance = vertHitDistance;
        rays[i].wall_hit_x = vertWallHitX;
        rays[i].wall_hit_y = vertWallHitY;
        rays[i].was_hit_vertical = 1;
    }
    else
    {
        rays[i].distance = horzHitDistance;
        rays[i].wall_hit_x = horzWallHitX;
        rays[i].wall_hit_y = horzWallHitY;
        rays[i].was_hit_vertical = 0;
    }
    rays[i].ray_angle = ray_angle;
    rays[i].ray_facingdown = isRayFacingDown;
    rays[i].ray_facingup = isRayFacingUp;
    rays[i].ray_facingleft = isRayFacingLeft;
    rays[i].ray_facingright = isRayFacingRight;
    return (0);
}

void cast_all_rays()
{
    int columnId = 0;
    int i = 0;
    float ray_angle = player.rotation_angle - (FOV_ANGLE / 2);
    window.num_rays = window.width;
    while (i < window.num_rays)

    {
        cast_ray(ray_angle, columnId);
        ray_angle += (FOV_ANGLE / window.num_rays);
        columnId++;
        i++;
    }
}

void render_ray(int index)
{
    draw_line(player.x, player.y, rays[index].wall_hit_x, rays[index].wall_hit_y);
}
