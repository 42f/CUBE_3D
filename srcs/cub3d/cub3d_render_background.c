/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_background.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 10:00:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/10 14:56:12 by bvalette         ###   ########.fr       */
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
	while (y < data->res->y)
	{
		color = data->colors->f_color;
		if (SHADOW == TRUE)
		{
			shade = (0xFF * (y_floor / (double)half_screen));
			color |= (shade << 24);
		}
		ft_imgset(&data->img[BG]->data[y * data->img[BG]->size_line],
											color, data->img[BG]->size_line);
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
	while (y < half_screen)
	{
		color = data->colors->c_color;
		if (SHADOW == TRUE)
		{
			shade = (0xFF * (y / (double)half_screen));
			color |= (shade << 24);
		}
		ft_imgset(&data->img[BG]->data[y * data->img[BG]->size_line],
											color, data->img[BG]->size_line);
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
