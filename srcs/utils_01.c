/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 13:32:59 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 13:47:58 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int		ft_intersect_orientation(double alpha, int orientation_flag)
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

int		ft_cell_type(t_data *data, t_coord in, double alpha, int flag)
{
	int			x;
	int			y;

	if (flag == VERTICAL)
	{
		in.y--;
		in.x = (alpha > 90 && alpha < 270) ? in.x - 1 : in.x + 1;
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
	if (data->map->grid[y][x] == 1)
		return (WALL);
	else if (data->map->grid[y][x] == 2)
		return (SPRITE);
	else
		return (EMPTY);
}

void	ft_imgset(int *img, int color, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		img[i] = color;
		i++;
	}
}

int		ft_add_shade(t_data *data, int color, double y)
{
	double		shadow;
	t_RGB_int	new;

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

void	ft_print_error(t_data *data, int ret)
{
	if (ret == FALSE)
		write(1, "\033[0;31mError\nUSAGE ./cub3d cub [--save] \033[0m\n\n", 45);
	else if (ret == ERROR_MALLOC || ret == ERROR_MALLOC_IM)
		write(1, "\033[0;31mError\nMALLOC ERROR    \033[0m\n\n", 35);
	else if (ret == ERROR_TEXTURE_IMPORT)
		write(1, "\033[0;31mError\nCAN'T IMPORT TEXTURE  \033[0m\n\n", 40);
	else if (ret == ERROR_MAP)
		write(1, "\033[0;31mError\nMAP NOT CORRECT \033[0m\n\n", 35);
	else if (ret == ERROR_PLAYER)
		write(1, "\033[0;31mError\nPLAYER ERROR    \033[0m\n\n", 35);
	else if (data->map->set == ERROR)
		write(1, "\033[0;31mError\nMAP ERROR IN CUB\033[0m\n\n", 35);
	else if (data->map->set == ERROR_MALLOC)
		write(1, "\033[0;31mError\nMALLOC ERROR    \033[0m\n\n", 35);
	else if (ret == ERROR_MLX)
		write(1, "\033[0;31mError\nISSUE WITH MLX  \033[0m\n\n", 35);
	else if (ret == ERROR_FILE)
		write(1, "\033[0;31mError\nWRONG CUB  FILE \033[0m\n\n", 35);
	else if (ret == ERROR_TEXTURE)
		write(1, "\033[0;31mError\nISSUE W/ TEXTURE\033[0m\n\n", 35);
	else if (ret == ERROR_EXPORT)
		write(1, "\033[0;31mError\nCOULD NOT EXPORT\033[0m\n\n", 35);
	else if (ret != TRUE)
		write(1, "\033[0;31mError\nCUB FILE FAULTY \033[0m\n\n", 35);
}
