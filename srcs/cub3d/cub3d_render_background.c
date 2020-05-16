/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_background.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 10:00:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/16 12:19:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
static void	ft_set_floor(t_data *data, int y_floor)
{
	int	y;
	int color;
	int	shade;
	int	half_screen;

	half_screen = (int)data->res->y >> 1;
	y = y_floor;
	color = data->colors->f_color;
	while (y < data->res->y)
	{
		if (SHADOW == TRUE)
		{
			shade = (0xFF * (y_floor / (double)half_screen));
			color |= (shade << 24);
		}
		ft_imgset(&data->img[VIEW]->data[y * data->img[VIEW]->size_line],
											color, data->img[VIEW]->size_line);
		y_floor--;
		y++;
	}
}

static void	ft_set_ceiling(t_data *data, int *y_floor)
{
	int	y;
	int color;
	int	shade;
	int	half_screen;

	half_screen = (int)data->res->y >> 1;
	y = 0;
	color = data->colors->c_color;
	while (y < half_screen)
	{
		if (SHADOW == TRUE)
		{
			shade = (0xFF * (y / (double)half_screen));
			color |= (shade << 24);
		}
		ft_imgset(&data->img[VIEW]->data[y * data->img[VIEW]->size_line],
											color, data->img[VIEW]->size_line);
		y++;
	}
	*y_floor = y;
}
*/


static void	ft_set_floor(t_data *data, int x, int y, int color)
{
	int	shade;
	
	if (SHADOW == TRUE)
	{
		shade = (0xFF * (y / (data->res->y / 2)));
		color |= (shade << 24);
	}
	data->img[VIEW]->data[x + y * data->img[VIEW]->size_line] = color;
}

static void	ft_set_ceiling(t_data *data, int x, int y, int color)
{
	int	shade;
	
	if (SHADOW == TRUE)
	{
		shade = (0xFF * (y / (data->res->y / 2)));
		color |= (shade << 24);
	}
	data->img[VIEW]->data[x + y * data->img[VIEW]->size_line] = color;
}

void		ft_render_background(t_data *data, int x, int y_wallstart, int y_wallend)
{
	int y;
	int	color;

	y = 0;
	color = data->colors->c_color;
	while (y < y_wallstart)
	{
		ft_set_ceiling(data, x, y, color);
		y++;
	}
	y = y_wallend;
	color = data->colors->f_color;
	while (y < data->res->y)
	{
		ft_set_floor(data, x, y, color);
		y++;
	}
}
