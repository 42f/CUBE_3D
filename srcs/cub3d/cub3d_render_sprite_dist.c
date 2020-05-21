/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_sprite_dist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:41:06 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 12:06:17 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void			ft_compute_sp_dist(t_data *data)
{
	int			i;
	double		x_offset;
	double		y_offset;
	double		dist;

	i = 0;
	while (i < data->map->sp_qty)
	{
		if (data->map->sp[i]->index_in != -1)
		{
			x_offset = fabs(data->player->x - data->map->sp[i]->coord.x);
			y_offset = fabs(data->player->y - data->map->sp[i]->coord.y);
			dist = hypot(x_offset, y_offset);
			data->map->sp[i]->dist = dist;
			data->map->sp[i]->height = ((data->res->x / 2) / tan(ft_torad(30)));
			data->map->sp[i]->height *= UNIT / dist;
		}
		else
		{
			data->map->sp[i]->dist = -1;
			data->map->sp[i]->height = -1;
		}
		i++;
	}
}

void			ft_init_sp(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->map->sp_qty)
	{
		data->map->sp[i]->index_in = -1;
		data->map->sp[i]->index_out = -1;
		data->map->sp[i]->index_len = -1;
		data->map->sp[i]->dist = -1;
		data->map->sp[i]->height = -1;
		i++;
	}
}

void			ft_set_sp_index_len(t_data *data)
{
	int			i;
	t_sprite	*sp;

	i = 0;
	while (i < data->map->sp_qty)
	{
		sp = data->map->sp[i];
		if (sp->index_in != -1)
			sp->index_len = sp->index_out - sp->index_in;
		i++;
	}
}

void			ft_sort_sp_dist(t_data *data)
{
	int			i;
	int			y;
	t_sprite	*swap;

	i = 0;
	y = 1;
	while (y < data->map->sp_qty)
	{
		if (data->map->sp[i]->dist < data->map->sp[y]->dist)
		{
			swap = data->map->sp[i];
			data->map->sp[i] = data->map->sp[y];
			data->map->sp[y] = swap;
			i = 0;
			y = 1;
			continue ;
		}
		i++;
		y++;
	}
}
