#ifndef HEADER_H
#define HEADER_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mlx.h"

#define BUFFER_SIZE 1024
#define PI 3.14159265
#define TWO_PI 6.28318530
#define PI_TWO (PI * 2)
#define FOV_ANGEL (60 * (PI / 180))
#define RADIUN (PI / 180)
#define WALK_SPEED 1.0
#define TURN_SPEED (1 * RADIUN)
#define FOV_ANGLE (60 * RADIUN)
#define RAY_WIDTH 1

typedef struct s_ray
{
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    int was_hit_vertical;
    int ray_facingdown;
    int ray_facingup;
    int ray_facingright;
    int ray_facingleft;
} t_ray;

typedef struct s_data
{
    void *pointer;
    void *image;
    void *window;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

typedef struct s_win
{
    float tile_size;
    float width;
    float height;
    float num_rays;
    int num_map_rows;
    int num_map_cols;
    char **array;
    char chr;
} t_win;

typedef struct s_player
{
    float x;
    float y;
    float radius;
    int turn_direction;
    int walk_direction;
    int side_direction;
    float rotation_angle;
    float move_speed;
    char last_move;
} t_player;

t_win window;
t_player player;
t_data mlx;
t_ray rays[10000];

int get_next_line(int fd, char **line);
size_t ft_strlen(const char *s);
size_t ft_len(char *s, char c);
char *ft_strdup(const char *s1);
char *ft_strjoin(char const *s1, char const *s2, int z);
char *ft_substr(char const *s, unsigned int start, size_t len);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
int ft_atoi(const char *str);
void *ft_memchr(const void *s, int c, size_t n);
char *ft_strrchr(const char *str, int c);
void read_file(char *p);
void ft_putstr(char *s);
char **ft_split(char const *s, char c);
int key_pressed(int key, void *param);
int key_released(int key, void *param);
void ft_exit(int i);
void ft_square(int x, int y, int color);
void map_render();
void render_player(int x, int y);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void setup();
int update(void *param);
void render();
void setup_player();
void update_player();
int is_this_wall(float x, float y);
void draw_line(float x1, float y1, float x2, float y2);
void cast_all_rays();
int cast_ray(float ray_angle, int i);
void render_ray(int index);
void *ft_free(char **s, int i);
#endif
