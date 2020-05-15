/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_view.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 10:42:23 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/15 16:42:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include <math.h>

static int	ft_get_pixel(t_data *data, t_intersect wall, int x, int y, int shade)
{
	int				cursor;
	int				color;
	static t_coord	last_coord;
	static int		last_color;

	y = (UNIT / wall.height) * y;
	y = fmod(y ,UNIT);
	if (last_coord.y == y && last_coord.x == x)
		return (last_color);
	cursor = (x + data->img[wall.flag]->size_line * y);
	color = data->img[wall.flag]->data[cursor];
	color |= shade;
	last_coord.x = x;
	last_coord.y = y;
	last_color = color;
	return (color);
}

static int	ft_get_x_coord(t_data *data, t_intersect wall)
{
	int	 	x_ret;

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

static void		ft_draw_column(t_data *data, int col, t_intersect wall, int shade)
{
	t_coord	coord;
	int		y_wallstart;
	int		y_wallend;
	int		cursor;
	int		y_offset;
	
	y_wallstart = (wall.height >= data->res->y) ? 0 : (data->res->y - wall.height) / 2;
	y_offset = (wall.height >= data->res->y) ? (data->res->y - wall.height) / 2 : y_wallstart;
	y_wallend = data->res->y - y_wallstart;
	coord.y = y_wallstart;
	coord.x = ft_get_x_coord(data, wall);
	while (coord.y < y_wallend)
	{
		cursor = ft_pos(col, coord.y, data->img[VIEW]->size_line);
		data->img[VIEW]->data[cursor] = ft_get_pixel(data, wall, coord.x,
													coord.y - y_offset, shade);
		//data->img[BG]->data[cursor] = 0xFF000000;
		coord.y++;
	}
}

t_intersect		ft_find_wall(t_data *data, double alpha)
{
	t_intersect	proj_hor;
	t_intersect	proj_ver;

	proj_hor = ft_wall_horizontal(data, alpha);
	proj_ver = ft_wall_vertical(data, alpha);
	if (proj_ver.dist < proj_hor.dist)
	{
		proj_ver.flag = ft_intersect_orientation(alpha, VERTICAL);
		return (proj_ver);
	}
	else
	{	
		proj_hor.flag = ft_intersect_orientation(alpha, HORIZONTAL);
		return (proj_hor);
	}
}

static void			ft_render_walls(t_data *data)
{
	int			column;
	t_intersect	wall;
	double		alpha;
	int			shade;

	column = 0;
	shade = 0;
	while (column < data->res->x)
	{
		alpha = (data->player->a + 30) - ((60 / data->res->x) * column);
		alpha = ft_map_alpha(alpha);
		wall = ft_find_wall(data, alpha);
		if (column < data->res->x / 2)
			wall.dist *= cos(ft_torad(alpha - data->player->a));
		else
			wall.dist *= cos(ft_torad(data->player->a - alpha));
		wall.height = UNIT / wall.dist * ((data->res->x / 2) / tan(ft_torad(30)));
		if (SHADOW == TRUE)
			shade = ft_get_shade(wall.dist);
		ft_draw_column(data, column, wall, shade);
		ft_draw_column(data, column + 1, wall, shade);
		column += 2;
	}
}

int			ft_render_view(t_data *data)
{
	int		ret;

//	debug_printdata(data, 1);
//	mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr);

	ft_render_background(data);
	ft_render_walls(data);
	ret = ft_render_sprite(data);

	ft_imgset(data->img[BG]->data, 0x00FF0000,
									data->img[BG]->size_line * data->res->y);
	ft_imgset(data->img[VIEW]->data, 0x00000000,
									data->img[VIEW]->size_line * data->res->y);
	ft_imgset(data->img[SP_VIEW]->data, 0xFF000000,
								data->img[SP_VIEW]->size_line * data->res->y);

//	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
//													data->img[BG]->ptr, 0, 0);
//	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
//													data->img[VIEW]->ptr, 0, 0);

	ft_imgset(data->img[SP]->data, GREEN, 0);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
												data->img[SP]->ptr, 10, 10);
	return (ret);
}
