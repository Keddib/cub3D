#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BUFFER_SIZE 1024
#define PI 3.14159265
#define TWO_PI 6.28318530
#define PI_TWO (PI * 2)
#define FOV_ANGEL (60 * (PI / 180))
#define RADIUN (PI / 180)
#define WALK_SPEED 1.6
#define TURN_SPEED (1 * RADIUN)
#define FOV_ANGLE (60 * RADIUN)
#define RAY_WIDTH 1
#define INT_MAX 2147483647
#define TILE_SIZE 64

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
    int wall_top;
    int wall_bottom;
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

typedef struct s_incept
{
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;
    float horz_x;
    float horz_y;
    float vert_x;
    float vert_y;
    float horz_distance;
    float vert_distance;
    float check_x;
    float check_y;
    int is_horz_hit;
    int is_vert_hit;

} t_incept;

t_win window;
t_player player;
t_data mlx;

#endif