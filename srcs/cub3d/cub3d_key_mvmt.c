/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_key_mvmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 14:17:17 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/20 18:06:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void		ft_move_sp_off(t_data *data, int key, int factor, int alpha)
{
	double		dist_wall;
	t_intersect	proj_ver;
	t_intersect	proj_hor;
	t_coord		new;
	int			inter_flag;

	proj_ver = ft_wall_vertical(data, alpha);
	proj_hor = ft_wall_horizontal(data, alpha);
	dist_wall = (proj_ver.dist < proj_hor.dist) ? proj_ver.dist : proj_hor.dist;
	new.x = data->player->x + cos(alpha * (M_PI / 180)) * factor;
	new.y = data->player->y - sin(alpha * (M_PI / 180)) * factor;
	inter_flag = (proj_ver.dist < proj_hor.dist) ? VERTICAL : HORIZONTAL;
	if (ft_cell_type(data, new, alpha, inter_flag) != WALL)
	{
		data->player->x = new.x;
		data->player->y = new.y;
	}
	else if (factor > MINIMAL_DIST)
		ft_move_sp_off(data, key, factor - 1, alpha);
}

static void		ft_move_sp_on(t_data *data, int key, int factor, int alpha)
{
	double		dist_wall;
	t_intersect	proj_ver;
	t_intersect	proj_hor;
	t_coord		new;
	int			inter_flag;

	proj_ver = ft_wall_vertical(data, alpha);
	proj_hor = ft_wall_horizontal(data, alpha);
	dist_wall = (proj_ver.dist < proj_hor.dist) ? proj_ver.dist : proj_hor.dist;
	new.x = data->player->x + cos(alpha * (M_PI / 180)) * factor;
	new.y = data->player->y - sin(alpha * (M_PI / 180)) * factor;
	inter_flag = (proj_ver.dist < proj_hor.dist) ? VERTICAL : HORIZONTAL;
	if (ft_cell_type(data, new, alpha, inter_flag) != WALL
	&& ft_cell_type(data, new, alpha, inter_flag) != SPRITE)
	{
		data->player->x = new.x;
		data->player->y = new.y;
	}
	else if (factor > MINIMAL_DIST + 10)
		ft_move_sp_on(data, key, factor - 1, alpha);
}

static void		ft_rotation(t_data *data, int key, int factor)
{
	if (key == LEFT_ARROW)
		data->player->a += factor;
	if (key == RIGHT_ARROW)
		data->player->a -= factor;
	data->player->a = ft_map_alpha(data->player->a);
}

int				ft_movement_dispatch(t_data *data, int key)
{
	int			factor;
	int			alpha;

	factor = MOVEMENT_FACTOR;
	if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY)
	{
		alpha = (int)data->player->a;
		if (key == D_KEY)
			alpha = ft_map_alpha(alpha - 90);
		else if (key == A_KEY)
			alpha = ft_map_alpha(alpha + 90);
		else if (key == S_KEY)
			alpha = ft_map_alpha(alpha + 180);
		if (SOLID_SPRITE == TRUE)
			ft_move_sp_on(data, key, factor, alpha);
		else
			ft_move_sp_off(data, key, factor, alpha);
	}
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		ft_rotation(data, key, factor);
	return (TRUE);
}
