/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render_view_putimages.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:57:19 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/25 18:22:36 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	ft_put_images_view(t_data *data)
{
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
	data->img[VIEW]->ptr, 0, 0);
	if (data->player->fire &= TRUE)
	{
		mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
data->img[GUN_1]->ptr, data->res->x / 2 - data->img[GUN_1]->width / 2,
data->res->y - data->img[GUN_1]->height);
	}
	else
	{
		mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
data->img[GUN_0]->ptr, data->res->x / 2 - data->img[GUN_0]->width / 2,
data->res->y - data->img[GUN_0]->height);
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
data->img[TARGET]->ptr, data->res->x / 2 - data->img[TARGET]->width / 2,
data->res->y / 2 - data->img[TARGET]->height / 2);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
data->img[LIFEBAR]->ptr, 10, 10);
}
