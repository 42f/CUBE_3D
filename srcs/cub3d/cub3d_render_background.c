/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_background.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 10:00:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/16 22:05:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_set_floor(t_data *data, int x, int y, int color)
{
	if (SHADOW == TRUE)
		color = ft_add_shade(data, color, y);
	data->img[VIEW]->data[x + y * data->img[VIEW]->size_line] = color;
}

static void	ft_set_ceiling(t_data *data, int x, int y, int color)
{
	if (SHADOW == TRUE)
		color = ft_add_shade(data, color, data->res->y / 2 - y);
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
