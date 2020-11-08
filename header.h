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
#include "constants.h"
#include "mlx.h"

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
void ft_putstr(char *s);
char **ft_split(char const *s, char c, int *cols);
void read_file(char *p, t_all *all);
int key_pressed(int key, t_all *all);
int key_released(int key, t_all *all);
int ft_exit(int i, t_all *all);
void render_player(int x, int y);
void my_mlx_pixel_put(t_all *all, int x, int y, int color);
void update_player(t_all *all);
int is_this_wall(float x, float y, t_all *all, int q);
void cast_all_rays(t_all *all);
void render_ray(t_ray *ray);
void *ft_free(char **s, int i);
void get_horizontal(t_all *all, int i);
void get_vertical(t_all *all, int i);
float distance_between_points(float x1, float y1, float x2, float y2);
void calc_distances(t_all *all);
void *load_images(t_all *all);
void render_3d_projection(t_all *all);
int change_rgb(char *s, t_all *all);
int str_containe(char **s, int n);
void find_sprite(t_all *all);
float 	sprite_dis_to_fpp(t_all *all, float x, float y);
void	ft_sprites(t_all *all);
float   normlize_angle(float angle);
int		ft_strcmp(const char *s1, const char *s2);
int     create_bmp(t_all *all);
void    int_to_rgb(t_all *all, unsigned int color);
void    save_bmp(t_all *all);

#endif
