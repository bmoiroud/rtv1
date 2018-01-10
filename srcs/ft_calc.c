/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 15:20:24 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/30 20:59:21 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_get_thread_id(t_data data)
{
	pthread_t	s;
	int			i;

	i = 0;
	s = pthread_self();
	while (data.t[i] != s)
		i++;
	return (i);
}

void	*ft_calc(void *param)
{
	t_data	data;
	double	ax;
	double	ay;

	data = *(t_data *)param;
	data->win.x = ft_get_thread_id(data);
	data->win.y = 0;
	ax = data->rtv1.eye.rot.x - (FOV_X / 2) + data->rtv1.ax * data->win.x;
	ay = data->rtv1.eye.rot.y - (FOV_Y / 2);
	while (data->win.x < data->win.width)
	{
		while (++data->win.y < data->win.height)
		{
			ay += data.rtv1.ay * NB_THREADS;

		}
		ax += data.rtv1.ax * NB_THREADS;
		data.win.x += NB_THREADS;
	}
	pthread_exit(0);
}
