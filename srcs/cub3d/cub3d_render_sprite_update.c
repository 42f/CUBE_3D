/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_sprite_update.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:47:40 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 12:01:35 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	ft_get_cell_center(t_intersect *inter)
{
	if (inter->flag == EA)
	{
		inter->coord.x += UNIT / 2;
		inter->coord.y += UNIT / 2 - fmod(inter->coord.y, UNIT);
	}
	else if (inter->flag == WE)
	{
		inter->coord.x -= UNIT / 2;
		inter->coord.y += UNIT / 2 - fmod(inter->coord.y, UNIT);
	}
	else if (inter->flag == NO)
	{
		inter->coord.x += UNIT / 2 - fmod(inter->coord.x, UNIT);
		inter->coord.y -= UNIT / 2;
	}
	else if (inter->flag == SO)
	{
		inter->coord.x += UNIT / 2 - fmod(inter->coord.x, UNIT);
		inter->coord.y += UNIT / 2;
	}
}

void	ft_update_sp_data(t_data *data, double alpha,
												int index, t_intersect inter)
{
	int	i;

	alpha = ft_map_alpha(alpha);
	if (inter.flag == V_SPRITE)
		inter.flag = ft_intersect_orientation(alpha, VERTICAL);
	else
		inter.flag = ft_intersect_orientation(alpha, HORIZONTAL);
	ft_get_cell_center(&inter);
	i = 0;
	while (i < data->map->sp_qty)
	{
		if (inter.coord.x == data->map->sp[i]->coord.x
		&& inter.coord.y == data->map->sp[i]->coord.y)
			break ;
		i++;
	}
	if (i < data->map->sp_qty)
	{
		if (data->map->sp[i]->index_in == -1)
			data->map->sp[i]->index_in = index;
		else if (data->map->sp[i]->index_in != -1)
			data->map->sp[i]->index_out = index;
	}
}
