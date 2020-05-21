/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 14:02:48 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 12:01:08 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void			ft_next_cell(t_intersect *inter, double alpha)
{
	if (alpha > 90 && alpha < 270)
		inter->coord.x--;
	else if (alpha <= 90 || alpha >= 270)
		inter->coord.x++;
	if (alpha < 180)
		inter->coord.y--;
	else if (alpha > 180)
		inter->coord.y++;
}

static t_intersect	ft_find_sprite(t_data *data, double alpha, t_coord origin)
{
	t_intersect	proj_hor;
	t_intersect	proj_ver;
	t_intersect output;

	alpha = ft_map_alpha(alpha);
	proj_hor = ft_sp_horizontal(data, alpha, origin);
	proj_ver = ft_sp_vertical(data, alpha, origin);
	output.flag = ERROR;
	if (proj_ver.dist < proj_hor.dist && proj_ver.flag != ERROR)
	{
		proj_ver.flag = (proj_ver.flag == WALL) ? V_WALL : V_SPRITE;
		return (proj_ver);
	}
	else if (proj_hor.flag != ERROR)
	{
		proj_hor.flag = (proj_hor.flag == WALL) ? H_WALL : H_SPRITE;
		return (proj_hor);
	}
	else
		return (output);
}

static void			ft_locate_visible_sprites(t_data *data)
{
	int			index;
	double		alpha;
	double		end_scan;
	t_intersect inter;

	index = 0;
	alpha = ft_map_alpha(data->player->a + 90);
	end_scan = ft_map_alpha(data->player->a - 90);
	while (alpha != end_scan)
	{
		alpha = data->player->a + 90 - (60 / data->res->x * index);
		alpha = ft_map_alpha(alpha);
		inter.coord.x = data->player->x;
		inter.coord.y = data->player->y;
		inter.flag = TRUE;
		while (inter.flag != ERROR)
		{
			inter = ft_find_sprite(data, alpha, inter.coord);
			if (inter.flag == V_SPRITE || inter.flag == H_SPRITE)
				ft_update_sp_data(data, alpha, index, inter);
			ft_next_cell(&inter, alpha);
		}
		index++;
	}
}

int					ft_render_sprite(t_data *data)
{
	if (data->map->sp_qty == 0)
		return (TRUE);
	ft_init_sp(data);
	ft_locate_visible_sprites(data);
	ft_compute_sp_dist(data);
	ft_set_sp_index_len(data);
	ft_sort_sp_dist(data);
	ft_render_visible_sp(data);
	return (TRUE);
}
