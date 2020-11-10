/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:44:34 by keddib            #+#    #+#             */
/*   Updated: 2020/11/10 03:02:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define BUFFER_SIZE 1024
# define PI 3.14159265
# define TWO_PI 6.28318530
# define PI_TWO (PI * 2)
# define FOV_ANGEL (60 * (PI / 180))
# define RADIUN (PI / 180)
# define WALK_SPEED 5
# define TURN_SPEED (3 * RADIUN)
# define FOV_ANGLE (60 * RADIUN)
# define RAY_WIDTH 1
# define INT_MAX 2147483647
# define TILE_SIZE 64

typedef char*	t_string;

typedef	struct	s_rgb
{
	int r;
	int g;
	int b;

}				t_rgb;

typedef struct	s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		facingdown;
	int		facingup;
	int		facingright;
	int		facingleft;
	int		wall_top;
	int		wall_bottom;
}				t_ray;

typedef struct	s_data
{
	void	*ptr;
	void	*img;
	void	*win;
	char	*addr;
	int		bpp;
	int		line_n;
	int		endian;
}				t_data;

typedef struct	s_win
{
	float	width;
	float	height;
	float	half_win;
	float	look;
	float	proj_plane;
	int		rows;
	int		cols;
	char	**array;
	char	chr;
}				t_win;

typedef struct	s_player
{
	float	x;
	float	y;
	float	rotation_angle;
	int		turn_direction;
	int		walk_direction;
	int		side_direction;
}				t_player;

typedef struct	s_incept
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	horz_x;
	float	horz_y;
	float	vert_x;
	float	vert_y;
	float	horz_distance;
	float	vert_distance;
	float	check_x;
	float	check_y;
	int		is_horz_hit;
	int		is_vert_hit;

}				t_incept;

typedef struct	s_texture
{
	void			*img;
	unsigned int	*data[5];
	char			*file[5];
	int				width;
	int				height;
	int				color[2];
}				t_texture;

typedef struct	s_file
{
	int		map_found;
	int		counter;
	int		res;
}				t_file;

typedef struct	s_sprite
{
	float	x;
	float	y;
	float	angle;
	float	distance;
	float	size;
	int		offx;
	int		offy;
}				t_sprite;

typedef struct	s_bmp
{
	unsigned char	*buffer;
	unsigned char	header[54];
	unsigned char	planes;
	unsigned int	file_size;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	unsigned int	bits_ppixel;
	unsigned int	image_size;
	int				row_bytes;

}				t_bmp;

typedef struct	s_all
{
	t_win		win;
	t_player	fpp;
	t_file		file;
	t_texture	tex;
	t_incept	incept;
	t_ray		*ray;
	t_sprite	*sprite;
	t_rgb		rgb;
	char		*param1;
	char		*param2;
	int			num_sprt;
	int			save;
}				t_all;

t_bmp			g_bmp;
t_data			g_mlx;
t_string		g_messages[19];
float			g_half_win;

#endif
