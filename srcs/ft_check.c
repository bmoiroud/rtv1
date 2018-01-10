/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:17:23 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/30 20:27:52 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_check_numbers(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
	return (1);
}

int		ft_objectid(char *str)
{
	if (ft_strcmp(str, "sphere:") == 0)
		return (0);
	else if (ft_strcmp(str, "plan:") == 0)
		return (1);
	else if (ft_strcmp(str, "cone:") == 0)
		return (2);
	else if (ft_strcmp(str, "cylinder:") == 0)
		return (3);
	else if (ft_strcmp(str, "light:") == 0)
		return (4);
	else
		return (-1);
}

void	ft_default_value(t_object *objs, t_win *win, t_rtv1 *rtv1)
{
	int		i;

	i = -1;
	while (&(objs[++i]))
		if (objs[i].color == -1)
			objs[i].color = COLOR;
		else if (objs[i].brightness == -1)
			objs[i].brightness = 0;
	if (win->width <= WIN_W_MIN)
		win->width = WIN_W;
	if (win->height <= WIN_H_MIN)
		win->height = WIN_H;
	rtv1->ax = FOV_X / win->width;
	rtv1->ay = FOV_X / win->height;
}
