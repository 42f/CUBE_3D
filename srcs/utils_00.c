/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 08:57:12 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/16 18:20:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

double	ft_map_alpha(double alpha)
{
	if (alpha >  360)
		alpha = alpha - 360;
	else if (alpha < 0)
		alpha = alpha + 360;
	return (alpha);
}

int	ft_col_conv(t_data *data, int r, int g, int b, int a)
{
	int			ret;

	if (data->win->endian == 1)
	{
		ret = (b << 8) | g;
		ret = (ret << 8) | r;
		ret = (ret << 8) | a;
	}
	else
	{
		ret = (a << 8) | r;
		ret = (ret << 8) | g;
		ret = (ret << 8) | b;
	}
	return (ret);
}

int	ft_cell_type(t_data *data, int **map, t_coord in, double alpha, int flag)
{
	int x; 
	int y;

	if (flag == VERTICAL)
	{
		in.y--;
		in.x = (alpha > 90  && alpha < 270) ? in.x - 1 : in.x + 1;
	}
	else if (flag == HORIZONTAL)
	{
		in.x--;
		in.y = (alpha > 0 && alpha < 180) ? in.y - 1 : in.y + 1;
	}
	x = ceil(in.x) / UNIT;
	y = ceil(in.y) / UNIT;
	if (x < 0 || x >= data->map->x)
		return (ERROR);
	if (y < 0 || y >= data->map->y)
		return (ERROR);
	if(map[y][x] == 1)
		return (WALL);
	else if(map[y][x] == 2)
		return (SPRITE);
	else
		return (EMPTY);
}

int	ft_pos(int x, int y, int size_line)
{
	return (x + size_line * y);
}

void	ft_imgset(int *img, int color, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		img[i] = color;
		i++;
	}
}

double	ft_torad(double x)
{
	return (x * (M_PI / 180));
}

int			ft_intersect_orientation(double alpha, int orientation_flag)
{
	int			intersection;

	intersection = 0;
	if (orientation_flag == HORIZONTAL)
	{
		if (alpha < 180)
			intersection = NO;
		else if (alpha > 180)
			intersection = SO;
	}
	else if (orientation_flag == VERTICAL)
	{
		if (alpha > 90 && alpha < 270)
			intersection = WE;
		else if (alpha < 90 || alpha > 270)
			intersection = EA;
	}
	return (intersection);
}

double		ft_convert_alpha(double alpha_deg)
{
	if (alpha_deg > 90 && alpha_deg <= 180)
		alpha_deg = 180 - alpha_deg;
	else if (alpha_deg > 180 && alpha_deg <= 270)
		alpha_deg = alpha_deg - 180;
	else if (alpha_deg > 270)
		alpha_deg = 360 - alpha_deg;
	return (alpha_deg);
}

int             ft_add_shade(t_data *data, int color, double y)
{
    double          shadow;
    t_RGB_int       new;

    shadow = tanh(y / data->res->y);
    if (data->win->endian == 0)
    {
            new.r = (color & 0x00ff0000) >> 16;
            new.r = (double)new.r * shadow;
            new.r <<= 16;
            new.g = (double)((color & 0x0000ff00) >> 8) * shadow;
            new.g <<= 8;
            new.b = (double)(color & 0x000000ff) * shadow;
            color = 0 | new.r | new.g | new.b;
    }
    else
    {
            new.r = (double)((color & 0x0000ff00) << 16) * shadow;
            new.r >>= 16;
            new.g = (double)((color & 0x00ff0000) << 8) * shadow;
            new.r >>= 8;
            new.b = (double)(color & 0xff000000) * shadow;
            color = 0 | new.b | new.g | new.r;
    }
    return (color);
}
