/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mouse_mvmt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 09:50:06 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/15 18:06:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int		ft_mouse_manager(int x, int y, void *param)
{
	t_data 			*data;
	static int		old_x;

	data = param;
	if (MOUSE == FALSE)
		return (TRUE);
	mlx_mouse_hide(data->win->mlx_ptr, data->win->win_ptr);
	/*mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
													data->img[VIEW]->ptr, 0, 0);
	*/
	if (old_x != 0)
	{
		data->player->a = ft_map_alpha(data->player->a + old_x - x);	
		ft_render_view(data);
	}
	mlx_mouse_move(data->win->mlx_ptr, data->win->win_ptr, 1, y);
	old_x = x;
	return (TRUE);	
}
