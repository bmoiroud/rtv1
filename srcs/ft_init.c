/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:07:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/30 20:26:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_init_ray(t_ray *ray, t_coord *a, t_coord b)
{
	ray->dx = fabs(b.x - a->x);
	ray->sx = a->x < b.x ? 1 : -1;
	ray->dy = fabs(b.y - a->y);
	ray->sy = a->y < b.y ? 1 : -1;
	ray->dz = fabs(b.z - a->z);
	ray->sz = a->z < b.z ? 1 : -1;
	ray->e2 = ray->err;
}

void	ft_init_data(t_data *data)
{
	t_win	*win;

	win = &data->win;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, data->win.width, data->win.height, \
																		"RTv1");
	win->img = mlx_new_image(win->mlx, data->win.width, data->win.height);
	win->data = mlx_get_data_addr(win->img, &win->bpp, &win->linelen, \
																&win->endian);
}

void	ft_init_objects(char *file, t_rtv1 *rtv1, int o, int l)
{
	char	*line;
	int		fd;

	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(1);
	while (get_next_line(fd, &line))
		if (ft_strcmp(line, "#") == 0)
			o++;
		else if (ft_strcmp(line, "light:") == 0)
			l++;
	close(fd);
	if ((rtv1->objects = (t_object *)malloc(o * sizeof(t_object))) == NULL)
		ft_error(3);
	if ((rtv1->lights = (t_light *)malloc(l * sizeof(t_light))) == NULL)
		ft_error(3);
	ft_bzero(rtv1->objects, o * sizeof(rtv1->objects[0]));
	ft_bzero(rtv1->lights, l * sizeof(rtv1->lights[0]));
	while (--o >= -1)
		rtv1->objects[o + 1].color = -1;
	while (--l >= -1)
		rtv1->objects[l + 1].color = -1;
}

void	ft_init_thread(t_data *data)
{
	int		i;

	i = -1;
	while (++i != NB_THREADS)
		if (pthread_create(&data->t[i], NULL, ft_calc, (void *)data) != 0)
			ft_error(4);
	i = -1;
	while (++i != NB_THREADS)
		if (pthread_join(data->t[i], NULL))
			ft_error(5);
}
