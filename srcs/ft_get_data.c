/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 22:29:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/30 19:20:46 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_get_size(t_size *size, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	line = NULL;
	if (get_next_line(fd, &line) == -1)
		ft_error(1);
	if (!(tab = ft_strsplit(line, ' ')))
		ft_error(3);
	if (!tab[0] || !tab[1] || !tab[2] || !ft_check_numbers(line) || size->set)
		ft_error(2);
	size->height = (double)ft_atoi(tab[0]);
	size->width = (double)ft_atoi(tab[1]);
	size->depth = (double)ft_atoi(tab[2]);
	size->set = 1;
	while (tab[++i])
		if (tab[i])
			free(tab[i]);
	free(line);
}

void	ft_get_color(int *color, int fd)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line) == -1)
		ft_error(1);
	if (line[1] == 'x')
		*color = ft_atoi_base(line + 2, 16);
	else if (ft_check_numbers(line))
		*color = ft_atoi(line);
	else
		ft_error(2);
	free(line);
}

void	ft_get_brightness(int *brightness, int fd)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line) == -1)
		ft_error(1);
	if (!ft_check_numbers(line))
		ft_error(2);
	*brightness = ft_atoi(line);
	free(line);
}

void	ft_get_coord(t_coord *pos, int fd)
{
	char	**tab;
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	tab = NULL;
	if (get_next_line(fd, &line) == -1)
		ft_error(1);
	if (!(tab = ft_strsplit(line, ' ')))
		ft_error(3);
	if (!tab[0] || !tab[1] || !tab[2] || !ft_check_numbers(line) || pos->set)
		ft_error(2);
	pos->x = (double)ft_atoi(tab[0]);
	pos->y = (double)ft_atoi(tab[1]);
	pos->z = (double)ft_atoi(tab[2]);
	pos->set = 1;
	while (tab[++i])
		if (tab[i])
			free(tab[i]);
	free(line);
}

void	ft_get_rotation(t_rotation *rotation, int fd)
{
	char	**tab;
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	tab = NULL;
	if (get_next_line(fd, &line) == -1)
		ft_error(1);
	if (!(tab = ft_strsplit(line, ' ')))
		ft_error(3);
	if (!tab[0] || !ft_check_numbers(line) || rotation->set)
		ft_error(2);
	rotation->rot_x = (double)ft_atoi(tab[0]);
	if (tab[1])
		rotation->rot_y = (double)ft_atoi(tab[1]);
	if (tab[2])
		rotation->rot_z = (double)ft_atoi(tab[2]);
	rotation->set = 1;
	while (tab[++i])
		if (tab[i])
			free(tab[i]);
	free(line);
}

void	ft_get_screen_size(t_win *win, int fd, char *str)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line) == -1)
		ft_error(1);
	if (ft_strcmp(str, "width:") && ft_check_numbers(line))
		win->width = ft_atoi(line);
	else if (ft_strcmp(str, "height:") && ft_check_numbers(line))
		win->height = ft_atoi(line);
	else
		ft_error(2);
	free(line);
}
