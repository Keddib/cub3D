#include "header.h"

void ft_square(int x, int y, int color)
{
  int p, p1;
  p1 = y;
  p = x;

  while (y <= p1 + TILE_SIZE)
  {
    x = p;
    while (x <= p + TILE_SIZE)
    {
      my_mlx_pixel_put(&mlx, x, y, color);
      x++;
    }
    y++;
  }
}

void map_render()
{
  int i = 0;
  int j = 0;
  int tile_x = 0;
  int tile_y = 0;
  int color;

  while (i < window.num_cols)
  {
    j = 0;
    while (j < window.num_rows)
    {
      tile_x = j * TILE_SIZE;
      tile_y = i * TILE_SIZE;
      color = window.array[i][j] == '1' ? 0xfff : 0x000;
      ft_square(tile_x, tile_y, color);
      j++;
    }
    i++;
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
void render_ray(t_ray *ray)
{
  draw_line(player.x, player.y, ray->wall_hit_x, ray->wall_hit_y);
}