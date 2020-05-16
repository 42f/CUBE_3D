/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_background.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 10:00:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/16 10:49:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void		ft_render_background(t_data *data)
{
	int	y_floor;

	ft_set_ceiling(data, &y_floor);
	ft_set_floor(data, y_floor);
}
