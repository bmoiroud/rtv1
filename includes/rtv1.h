/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:54:15 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/30 20:28:32 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIN_W 1200
# define WIN_H 800
# define WIN_W_MIN 300
# define WIN_H_MIN 200
# define IMG_W WIN_W
# define IMG_H WIN_H
# define IMG_W_MIN WIN_W_MIN
# define IMG_H_MIN WIN_H_MIN
# define FOV_X 60
# define FOV_Y 40
# define COLOR 16711680
# define INTENSITY 100
# define NB_THREADS 64

# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef struct	s_ray
{
	double		dx;
	double		dy;
	double		dz;
	double		sx;
	double		sy;
	double		sz;
	double		err;
	double		e2;
}				t_ray;

typedef struct	s_coord
{
	double		x;
	double		y;
	double		z;
	int			set;
}				t_coord;

typedef struct	s_size
{
	double		height;
	double		width;
	double		depth;
	int			set;
}				t_size;

typedef struct	s_rotation
{
	double		rot_x;
	double		rot_y;
	double		rot_z;
	int			set;
}				t_rotation;

typedef struct	s_light
{
	int			intensity;
	t_coord		pos;
}				t_light;

typedef struct	s_object
{
	int			color;
	int			type;
	int			brightness;
	t_size		size;
	t_coord		pos;
	t_rotation	rotation;
}				t_object;

typedef struct	s_eye
{
	t_coord		pos;
	t_rotation	rot;
}				t_eye;

typedef struct	s_rtv1
{
	double		ay;
	double		ax;
	t_object	*objects;
	t_light		*lights;
	t_eye		eye;
}				t_rtv1;

typedef struct	s_win
{
	int			x;
	int			y;
	int			bpp;
	int			endian;
	int			linelen;
	int			width;
	int			height;
	char		*data;
	void		*img;
	void		*mlx;
	void		*win;
}				t_win;

typedef struct	s_data
{
	t_win		win;
	t_rtv1		rtv1;
	pthread_t	t[NB_THREADS];
}				t_data;

void	ft_parse(char *file, t_data *data);
void	ft_cast_ray(t_ray *r, t_coord s, t_coord dst);
void	ft_init_ray(t_ray *ray, t_coord *a, t_coord b);
void	ft_init_data(t_data *data);
void	ft_get_dimension(t_object *obj, int fd);
void	ft_get_color(int *color, int fd);
void	ft_get_brightness(int *brightness, int fd);
void	ft_init_ray(t_ray *ray, t_coord *a, t_coord b);
void	ft_init_data(t_data *data);
void	ft_init_objects(char *file, t_rtv1 *rtv1, int o, int l);
void	ft_error(int error);
void	ft_get_coord(t_coord *pos, int fd);
void	ft_get_size(t_size *size, int fd);
void	ft_get_rotation(t_rotation *rotation, int fd);
void	ft_get_fov(t_eye *eye, int fd);
void	ft_init_thread(t_data *data);
void	*ft_calc(void *param);
void	ft_default_value(t_object *objs, t_win *win, t_rtv1 *rtv1);
int		ft_objectid(char *str);
int		ft_check_numbers(char *str);

#endif
