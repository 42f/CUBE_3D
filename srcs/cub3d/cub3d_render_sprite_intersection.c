/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_sprite_intersection.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 14:46:47 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/09 21:37:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <limits.h>

t_intersect		ft_sp_vertical(t_data *data, int **map, double alpha_deg, t_coord origin)
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
		inter.coord.x = floor(origin.x / UNIT) * UNIT;
	else
		inter.coord.x = ceil(origin.x / UNIT) * UNIT;
	x_offset = fabs(origin.x - inter.coord.x);
	inter.coord.y = origin.y + (x_offset * tan(beta_rad) * sign.y);
	output = ft_cell_type(data, map, inter.coord, alpha_deg, VERTICAL);
	while (output == EMPTY)
	{
		x_offset = fabs(origin.x - inter.coord.x);
		inter.coord.x += UNIT * sign.x;
		inter.coord.y += UNIT * tan(beta_rad) * sign.y;
		output = ft_cell_type(data, map, inter.coord, alpha_deg, VERTICAL);
	}
	inter.flag = output;
	x_offset = fabs(origin.x - inter.coord.x);
	inter.dist = fabs(x_offset / cos(beta_rad));
	return (inter);
}

t_intersect		ft_sp_horizontal(t_data *data, int **map, double alpha_deg, t_coord origin)
{
	double		beta_rad;
	double		y_offset;
	t_intersect	inter;
	t_ints		sign;
	int			output;

	sign.x = (alpha_deg > 90 && alpha_deg < 270) ? -1 : 1;
	sign.y = (alpha_deg < 180) ? -1 : 1;
	beta_rad = ft_torad(180 - 90 - ft_convert_alpha(alpha_deg));
	if (alpha_deg < 180)
		inter.coord.y = floor(origin.y / UNIT) * UNIT;
	else
		inter.coord.y = ceil(origin.y / UNIT) * UNIT;
	y_offset = fabs(origin.y - inter.coord.y);
	inter.coord.x = origin.x + (y_offset * tan(beta_rad) * sign.x);
	output = ft_cell_type(data, map, inter.coord, alpha_deg, HORIZONTAL);
	while (output == EMPTY)
	{
		inter.coord.y += UNIT * sign.y;
		inter.coord.x += UNIT * tan(beta_rad) * sign.x;
		output = ft_cell_type(data, map, inter.coord, alpha_deg, HORIZONTAL);
	}
	inter.flag = output;
	y_offset = fabs(origin.y - inter.coord.y);
	inter.dist = fabs(y_offset / cos(beta_rad));
	return (inter);
}

