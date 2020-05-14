/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mouse_mvmt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 09:50:06 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/14 16:45:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_mouse_manager(int x, int y, void *param)
{


(void)x;
(void)y;
(void)param;
	return (TRUE);
/*	t_data 			*data;
	static int		old_x;
	int				mouse_x;
	int				mouse_y;

	if (MOUSE == FALSE)
		return (TRUE);
	mlx_mouse_hide(data->win->mlx_ptr, data->win->win_ptr);
	data = param;
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
													data->img[VIEW]->ptr, 0, 0);
	if (old_x != 0)
	{
		data->player->a = ft_map_alpha(data->player->a + old_x - x);	
		ft_render_view(data);
	}
	mlx_mouse_move(data->win->mlx_ptr, data->win->win_ptr, 1, y);
	mlx_mouse_get_pos(data->win->win_ptr, &mouse_x , &mouse_y);
	old_x = mouse_x;
	return (TRUE);	
*/
}
