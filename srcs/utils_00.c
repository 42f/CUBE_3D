/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 08:57:12 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 13:42:00 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

double	ft_map_alpha(double alpha)
{
	if (alpha > 360)
		alpha = alpha - 360;
	else if (alpha < 0)
		alpha = alpha + 360;
	return (alpha);
}

int		ft_col_conv(t_data *data, int r, int g, int b)
{
	int		ret;

	if (data->win->endian == 1)
	{
		ret = (b << 8) | g;
		ret = (ret << 8) | r;
		ret = (ret << 8) | 0;
	}
	else
	{
		ret = (0 << 8) | r;
		ret = (ret << 8) | g;
		ret = (ret << 8) | b;
	}
	return (ret);
}

int		ft_pos(int x, int y, int size_line)
{
	return (x + size_line * y);
}

double	ft_torad(double x)
{
	return (x * (M_PI / 180));
}

double	ft_convert_alpha(double alpha_deg)
{
	if (alpha_deg > 90 && alpha_deg <= 180)
		alpha_deg = 180 - alpha_deg;
	else if (alpha_deg > 180 && alpha_deg <= 270)
		alpha_deg = alpha_deg - 180;
	else if (alpha_deg > 270)
		alpha_deg = 360 - alpha_deg;
	return (alpha_deg);
}
