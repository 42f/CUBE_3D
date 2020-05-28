/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mouse_mvmt_linux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 09:50:06 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/28 15:42:50 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_mouse_manager(int x, int y, void *param)
{
	t_data		*data;
	static int	old_x;

	data = param;
	if (MOUSE == FALSE)
		return (TRUE);
	mlx_mouse_hide(data->win->mlx_ptr, data->win->win_ptr);
	if (old_x != 0)
	{
		data->player->a = ft_map_alpha(data->player->a + old_x - x);
		ft_render_view(data);
	}
	mlx_mouse_move(data->win->mlx_ptr, data->win->win_ptr, 1, y);
	old_x = x;
	return (TRUE);
}
