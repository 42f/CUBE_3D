/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_view.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 10:42:23 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/24 20:04:31 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

static int	ft_get_pixel(t_data *data, t_intersect wall, int x, int y)
{
	int				cursor;
	int				color;
	static t_coord	last_coord;
	static int		last_color;

	y = (data->img[wall.flag]->height / wall.height) * y;
	y = fmod(y, data->img[wall.flag]->height);
	if (last_coord.y == y && last_coord.x == x)
		return (last_color);
	cursor = (x + data->img[wall.flag]->size_line * y);
	color = data->img[wall.flag]->data[cursor];
	if (SHADOW == TRUE)
	{
		if (wall.dist < 1000 && (color & BLUE) > 210)
			color = ft_add_shade(data, color, wall.height * 10);
		else
			color = ft_add_shade(data, color, wall.height);
	}
	last_coord.x = x;
	last_coord.y = y;
	last_color = color;
	return (color);
}

static int	ft_get_x_coord(t_data *data, t_intersect wall)
{
	int				x_ret;

	if (wall.flag == NO)
		x_ret = wall.coord.x;
	else if (wall.flag == SO)
		x_ret = data->img[wall.flag]->width - wall.coord.x;
	else if (wall.flag == EA)
		x_ret = wall.coord.y;
	else
		x_ret = data->img[wall.flag]->width - wall.coord.y;
	x_ret = fmod(abs(x_ret), data->img[wall.flag]->width);
	return (x_ret);
}

static void	ft_draw_column(t_data *data, int col, t_intersect wall)
{
	t_coord			coord;
	int				y_wallstart;
	int				y_wallend;
	int				cursor;
	int				y_offset;

	y_wallstart = (wall.height >= data->res->y) ?
							0 : (data->res->y - wall.height) / 2;
	y_offset = (wall.height >= data->res->y) ?
							(data->res->y - wall.height) / 2 : y_wallstart;
	y_wallend = data->res->y - y_wallstart;
	coord.y = y_wallstart;
	coord.x = ft_get_x_coord(data, wall);
	ft_render_bg(data, col, y_wallstart, y_wallend);
	while (coord.y <= y_wallend)
	{
		cursor = ft_pos(col, coord.y, data->img[VIEW]->size_line);
		data->img[VIEW]->data[cursor] = ft_get_pixel(data, wall, coord.x,
															coord.y - y_offset);
		coord.y++;
	}
}

static void	ft_render_walls(t_data *data)
{
	int				column;
	t_intersect		wall;
	double			alpha;

	column = 0;
	while (column < data->res->x)
	{
		alpha = (data->player->a + 30) - ((60 / data->res->x) * column);
		alpha = ft_map_alpha(alpha);
		wall = ft_find_wall(data, alpha);
		if (column < data->res->x / 2)
			wall.dist *= cos(ft_torad(alpha - data->player->a));
		else
			wall.dist *= cos(ft_torad(data->player->a - alpha));
		wall.height = UNIT / wall.dist;
		wall.height *= ((data->res->x / 2) / tan(ft_torad(30)));
		ft_draw_column(data, column, wall);
		ft_draw_column(data, column + 1, wall);
		column += 2;
	}
}

int			ft_render_view(t_data *data)
{
	int				ret;

	ft_render_walls(data);
	ret = ft_render_sprite(data);
	if (data->export_flag != TRUE)
	{
		mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
												data->img[VIEW]->ptr, 0, 0);
		mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
			data->img[GUN]->ptr, data->res->x / 2 - data->img[GUN]->width / 2,
			data->res->y - data->img[GUN]->height);
	}
	if (ret != TRUE)
		ft_free_all(data, ret);
	return (ret);
}
