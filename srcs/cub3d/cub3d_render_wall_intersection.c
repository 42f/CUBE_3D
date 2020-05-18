/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_wall_intersection.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 14:46:47 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/18 19:37:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <limits.h>

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
	x_offset = fabs(data->player->x - inter.coord.x);
	inter.dist = fabs(x_offset / cos(beta_rad));
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
	y_offset = fabs(data->player->y - inter.coord.y);
	inter.dist = fabs(y_offset / cos(beta_rad));
	return (inter);
}
