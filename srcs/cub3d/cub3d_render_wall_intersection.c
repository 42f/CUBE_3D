/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_wall_intersection.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 14:46:47 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/24 20:05:40 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_intersect		ft_wall_vertical(t_data *data, double alpha_deg)
{
	double		beta_rad;
	double		x_offset;
	t_intersect	inter;
	t_ints		sign;
	int			output;

	sign.x = (alpha_deg > 90 && alpha_deg < 270) ? -1 : 1;
	sign.y = (alpha_deg < 180) ? -1 : 1;
	beta_rad = ft_torad(ft_convert_alpha(alpha_deg));
	if (alpha_deg > 90 && alpha_deg < 270)
		inter.coord.x = floor(data->player->x / UNIT) * UNIT;
	else
		inter.coord.x = ceil(data->player->x / UNIT) * UNIT;
	x_offset = fabs(data->player->x - inter.coord.x);
	inter.coord.y = data->player->y + (x_offset * tan(beta_rad) * sign.y);
	output = ft_cell_type(data, inter.coord, alpha_deg, VERTICAL);
	while (output != WALL && output != ERROR)
	{
		x_offset = fabs(data->player->x - inter.coord.x);
		inter.coord.x += UNIT * sign.x;
		inter.coord.y += UNIT * tan(beta_rad) * sign.y;
		output = ft_cell_type(data, inter.coord, alpha_deg, VERTICAL);
	}
	inter.dist = fabs(fabs(data->player->x - inter.coord.x) / cos(beta_rad));
	return (inter);
}

t_intersect		ft_wall_horizontal(t_data *data, double alpha_deg)
{
	double		beta_rad;
	double		y_offset;
	t_intersect	inter;
	t_ints		sign;
	int			output;

	sign.x = (alpha_deg > 90 && alpha_deg < 270) ? -1 : 1;
	sign.y = (alpha_deg < 180) ? -1 : 1;
	beta_rad = ft_convert_alpha(alpha_deg);
	beta_rad = ft_torad(180 - 90 - beta_rad);
	if (alpha_deg < 180)
		inter.coord.y = floor(data->player->y / UNIT) * UNIT;
	else
		inter.coord.y = ceil(data->player->y / UNIT) * UNIT;
	y_offset = fabs(data->player->y - inter.coord.y);
	inter.coord.x = data->player->x + (y_offset * tan(beta_rad) * sign.x);
	output = ft_cell_type(data, inter.coord, alpha_deg, HORIZONTAL);
	while (output != WALL && output != ERROR)
	{
		inter.coord.y += UNIT * sign.y;
		inter.coord.x += UNIT * tan(beta_rad) * sign.x;
		output = ft_cell_type(data, inter.coord, alpha_deg, HORIZONTAL);
	}
	inter.dist = fabs(fabs(data->player->y - inter.coord.y) / cos(beta_rad));
	return (inter);
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
