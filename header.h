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
char **ft_split(char const *s, char c);
void read_file(char *p);
int key_pressed(int key, void *param);
int key_released(int key, void *param);
void ft_exit(int i);
void map_render();
void render_player(int x, int y);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void setup_player();
void update_player();
int is_this_wall(float x, float y);
t_ray *cast_all_rays();
void render_ray(t_ray *ray);
void *ft_free(char **s, int i);
void get_horizontal(t_ray *ray, t_incept *incept);
void get_vertical(t_ray *ray, t_incept *incept);
float distance_between_points(float x1, float y1, float x2, float y2);
void calc_distances(t_ray *ray, t_incept *incept);
t_texture *load_images();

#endif
