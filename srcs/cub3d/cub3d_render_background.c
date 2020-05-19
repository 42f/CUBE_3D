/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_background.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 10:00:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/19 11:07:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_render_bg(t_data *data, int x, int y_wallstart, int y_wallend)
{
	int y;
	int	color;
	int	half_screen;
	
	half_screen = data->res->y / 2;
	y = 0;
	while (y < y_wallstart)
	{
		color = data->colors->c_color;
		if (SHADOW == TRUE)
			color = ft_add_shade(data, color, half_screen - y);
		data->img[VIEW]->data[x + y * data->img[VIEW]->size_line] = color;
		y++;
	}
	y = y_wallend;
	while (y < data->res->y)
	{
		color = data->colors->f_color;
		if (SHADOW == TRUE)
			color = ft_add_shade(data, color, y - half_screen);
		data->img[VIEW]->data[x + y * data->img[VIEW]->size_line] = color;
		y++;
	}
}
