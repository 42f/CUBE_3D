/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_sprite_draw.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 12:06:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/25 20:55:58 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_data *g_data;

static void		ft_put_pixel(double dist, int x, int y, int cursor)
{
	int			cursor_color;
	int			color;

	y = (UNIT / dist) * y;
	y = fmod(y, UNIT);
	cursor_color = ft_pos(x, y, g_data->img[SP]->size_line);
	color = g_data->img[SP]->data[cursor_color];
	if (SHADOW == TRUE)
	{
		if (g_data->player->fire == TRUE && dist < 1500)
			color = ft_add_shade(g_data, color, dist * 100);
		else if (dist < 1000 && (color & BLUE) > 210)
			color = ft_add_shade(g_data, color, dist * 100);
		else
			color = ft_add_shade(g_data, color, dist);
	}
	if (color != 0)
		g_data->img[VIEW]->data[cursor] = color;
}

static void		ft_fill_column(int col, t_sprite sp, int index)
{
	t_coord		coord;
	int			y_start;
	int			y_end;
	int			cursor;
	int			y_offset;

	y_start = (sp.height >= g_data->res->y) ?
									0 : (g_data->res->y - sp.height) / 2;
	y_offset = (sp.height >= g_data->res->y) ?
									(g_data->res->y - sp.height) / 2 : y_start;
	y_end = g_data->res->y - y_start - 1;
	coord.y = y_start;
	coord.x = (index - sp.index_in) * g_data->img[SP]->width - 1;
	coord.x /= (sp.index_out - sp.index_in);
	while (coord.y < y_end)
	{
		cursor = ft_pos(col, coord.y, g_data->img[VIEW]->size_line);
		ft_put_pixel(sp.height, coord.x, coord.y - y_offset, cursor);
		coord.y++;
	}
}

static double	ft_get_wall_dist(double alpha)
{
	t_intersect	inter_wall;
	double		dist;
	int			x_offset;
	int			y_offset;

	alpha = ft_map_alpha(alpha);
	inter_wall = ft_find_wall(g_data, alpha);
	ft_get_cell_center(&inter_wall);
	x_offset = fabs(g_data->player->x - inter_wall.coord.x);
	y_offset = fabs(g_data->player->y - inter_wall.coord.y);
	dist = hypot(x_offset, y_offset);
	return (dist);
}

static void		ft_draw_column(int col, int index, double alpha)
{
	int			i;
	double		wall_dist;
	int			index_in;
	int			index_out;

	i = 0;
	wall_dist = ft_get_wall_dist(alpha);
	while (i < g_data->map->sp_qty)
	{
		if (g_data->map->sp[i]->index_in == -1)
			break ;
		index_in = g_data->map->sp[i]->index_in;
		index_out = g_data->map->sp[i]->index_out;
		if (wall_dist > g_data->map->sp[i]->dist
		&& index >= index_in
		&& index <= index_out
		&& g_data->map->sp[i]->dist > 35)
		{
			ft_fill_column(col, *g_data->map->sp[i], index);
		}
		i++;
	}
}

void			ft_render_visible_sp(t_data *data)
{
	int			index;
	int			col;
	double		alpha;
	double		end_scan;

	g_data = data;
	index = g_data->res->x;
	col = 0;
	alpha = g_data->player->a + 30;
	end_scan = g_data->player->a - 30;
	while (alpha > end_scan)
	{
		alpha = g_data->player->a + 30 - (60 / g_data->res->x * col);
		ft_draw_column(col, index, alpha);
		col++;
		index++;
	}
}
