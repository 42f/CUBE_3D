/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 14:02:48 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/15 17:40:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>


static void			ft_compute_sp_dist(t_data *data)
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
			x_offset = fabs(data->player->x	- data->map->sp[i]->coord.x);
			y_offset = fabs(data->player->y	- data->map->sp[i]->coord.y);
			dist = hypot(x_offset, y_offset);
			data->map->sp[i]->dist = dist;
			data->map->sp[i]->height = UNIT / dist * ((data->res->x / 2) / tan(ft_torad(30)));
		}
		else
		{
			data->map->sp[i]->dist = -1;
			data->map->sp[i]->height = -1;
		}
		i++;
	}
}


static void			ft_init_sp(t_data *data)
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

static void			ft_get_cell_center(t_intersect *inter)
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

static void			ft_set_sp_index_len(t_data *data)
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


static void			ft_update_sp_data(t_data *data, double alpha, int index, t_intersect inter)
{
	int			i;

	
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

static void		ft_sort_sp_dist(t_data *data)
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

static t_intersect	ft_find_sprite(t_data *data, double alpha, t_coord origin)
{
	t_intersect	proj_hor;
	t_intersect	proj_ver;
	t_intersect output;

	alpha = ft_map_alpha(alpha);
	proj_hor = ft_sp_horizontal(data, data->map->grid, alpha, origin);
	proj_ver = ft_sp_vertical(data, data->map->grid, alpha, origin);
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

static double		ft_get_wall_dist(t_data *data, double alpha)
{
	t_intersect	inter_wall;
	double		dist;
	int			x_offset;
	int			y_offset;

	alpha = ft_map_alpha(alpha);
	inter_wall = ft_find_wall(data, alpha);
	ft_get_cell_center(&inter_wall);
	x_offset = fabs(data->player->x	- inter_wall.coord.x);
	y_offset = fabs(data->player->y	- inter_wall.coord.y);
	dist = hypot(x_offset, y_offset);
	return (dist);
}

static void	ft_put_pixel(t_data *data, double dist, int x, int y, int cursor)
{
	int			cursor_color;
	int			color;

	y = (UNIT / dist) * y;
	y = fmod(y ,UNIT);
	cursor_color = ft_pos(x, y, data->img[SP]->size_line);
 	color = data->img[SP]->data[cursor_color];
	if (color != 0)
		data->img[VIEW]->data[cursor] = color;
}


static void		ft_fill_column(t_data *data, int col, t_sprite sp, int index)
{
	t_coord			coord;
	int				y_start;
	int				y_end;
	int				cursor;
	int				y_offset;

	y_start = (sp.height >= data->res->y) ? 0 : (data->res->y - sp.height) / 2;
	y_offset = (sp.height >= data->res->y) ? (data->res->y - sp.height) / 2 : y_start;
	y_end = data->res->y - y_start;
	coord.y = y_start;
	coord.x = (index - sp.index_in) * data->img[SP]->width - 1;
	coord.x /= (sp.index_out - sp.index_in);
	while (coord.y < y_end)
	{
		cursor = ft_pos(col, coord.y, data->img[VIEW]->size_line);
		ft_put_pixel(data, sp.height, coord.x, coord.y - y_offset, cursor);
		coord.y++;
	}
}

static void			ft_draw_column(t_data *data, int col, int index, double alpha)
{
	int			i;
	double		wall_dist;
	int 		index_in;
	int 		index_out;

	i = 0;
	wall_dist = ft_get_wall_dist(data, alpha);
	while (i < data->map->sp_qty)
	{
		if (data->map->sp[i]->index_in == -1)
			break ;
		index_in = data->map->sp[i]->index_in;
		index_out = data->map->sp[i]->index_out;
		if (wall_dist > data->map->sp[i]->dist
		&& index >= index_in  
		&& index <= index_out
		&& data->map->sp[i]->dist > 60)
		{
			ft_fill_column(data, col, *data->map->sp[i], index);
		}
		i++;
	}
}


static void			ft_render_visible_sp(t_data *data)
{
	int			index;
	int			col;
	double		alpha;
	double		end_scan;

	index = data->res->x;
	col = 0;
	alpha = data->player->a + 30;
	end_scan = data->player->a - 30;
	while (alpha > end_scan)
	{
		alpha = data->player->a + 30 - (60 / data->res->x * col);
		ft_draw_column(data, col, index, alpha);
		col++;
		index++;
	}
}

static void			ft_locate_all_sp(t_data *data)
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
		alpha = ft_map_alpha(data->player->a + 90 - (60 / data->res->x * index));
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
	ft_locate_all_sp(data);
	ft_compute_sp_dist(data);
	ft_set_sp_index_len(data);
	ft_sort_sp_dist(data);
	ft_render_visible_sp(data);	
	return (TRUE);
}
