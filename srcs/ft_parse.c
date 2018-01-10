/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 18:33:56 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/30 20:29:41 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_get_camera(int fd, t_rtv1 *rtv1, t_win *win)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line) == -1)
		ft_error(1);
	else if (ft_strcmp(line, "camera:") != 0)
		ft_error(1);
	while (ft_strcmp(line, "#") != 0)
	{
		free(line);
		if (get_next_line(fd, &line) == -1)
			ft_error(1);
		else if (ft_strcmp(line, "position:") == 0)
			ft_get_coord(&rtv1->eye.pos, fd);
		else if (ft_strcmp(line, "orientation:") == 0)
			ft_get_rotation(&rtv1->eye.rot, fd);
		else if (ft_strcmp(line, "width:") || ft_strcmp(line, "height:"))
			ft_get_screen_size(win, fd, line);
		else if (line[0] != '#' && line[1] != '#')
			ft_error(1);
	}
}

int		ft_get_object_data(int fd, t_rtv1 *rtv1, int i, int id)
{
	char	*line;

	line = NULL;
	while (ft_strcmp(line, "#") != 0)
	{
		if (get_next_line(fd, &line) == -1)
			ft_error(1);
		else if (ft_strcmp(line, "position:") == 0)
			ft_get_coord(&rtv1->objects[i].pos, fd);
		else if (ft_strcmp(line, "orientation:") == 0)
			ft_get_rotation(&rtv1->objects[i].rotation, fd);
		else if (ft_strcmp(line, "dimension:") == 0)
			ft_get_size(&rtv1->objects[i].size, fd);
		else if (ft_strcmp(line, "color:") == 0)
			ft_get_color(&rtv1->objects[i].color, fd);
		else if (ft_strcmp(line, "brightness:") == 0)
			ft_get_brightness(&rtv1->objects[i].brightness, fd);
		else if (line[0] != '#' && line[1] != '#')
			ft_error(2);
	}
	rtv1->objects[i].type = id;
	if (rtv1->objects[i].pos.set == 0 || rtv1->objects[i].size.set == 0)
		ft_error(2);
	return (1);
}

int		ft_get_light_data(int fd, t_rtv1 *rtv1, int j)
{
	char	*line;

	line = NULL;
	while (ft_strcmp(line, "#") != 0)
	{
		if (get_next_line(fd, &line) == -1)
			ft_error(1);
		else if (ft_strcmp(line, "position:") == 0)
			ft_get_coord(&rtv1->lights[j].pos, fd);
	}
	if (rtv1->lights[j].pos.set == 0)
		ft_error(2);
	return (1);
}

void	ft_get_objects(int fd, t_rtv1 *rtv1)
{
	char	*line;
	int		id;
	int		i;
	int		j;

	j = 0;
	i = 0;
	id = 0;
	line = NULL;
	while (ft_strcmp(line, "end") != 0)
	{
		free(line);
		if (get_next_line(fd, &line) == -1)
			ft_error(2);
		else if ((id = ft_objectid(line)) != -1)
		{
			if (id == 4)
				j += ft_get_light_data(fd, rtv1, j);
			else
				i += ft_get_object_data(fd, rtv1, i, id);
		}
		else if (line[0] != '#' && line[1] != '#' && ft_strcmp(line, "end"))
			ft_error(2);
	}
}

void	ft_parse(char *file, t_data *data)
{
	char	*line;
	int		fd;

	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(1);
	else if (get_next_line(fd, &line) == -1)
		ft_error(1);
	else if (ft_strcmp(line, "scene:") != 0)
		ft_error(2);
	free(line);
	ft_get_camera(fd, &data->rtv1, &data->win);
	ft_init_objects(file, &data->rtv1, 0, 0);
	ft_get_objects(fd, &data->rtv1);
	ft_default_value(&data->rtv1.objects, &data->win, &data->rtv1);
	close(fd);
}
