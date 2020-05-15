/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:13:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/15 15:13:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"

static int		ft_standard_rotation(t_data *data, int key)
{
	if (key == NUMPAD_2)
		data->player->a = 270;
	else if (key == NUMPAD_4)
		data->player->a = 180;
	else if (key == NUMPAD_6)
		data->player->a = 0;
	else if (key == NUMPAD_8)
		data->player->a = 90;
	return (ft_render_view(data));
}

int		ft_escape(t_data *data)
{
//		debug_printdata(data, 88);
		ft_free_all(data, TRUE);
		return (0);
//		system("leaks a.out");
//		exit (TRUE);
}

int		ft_key_manager(int key, void *param)
{
	t_data		*data;
	int			ret;
	
	ret = TRUE;
	data = (t_data *)param;
	mlx_mouse_show(data->win->mlx_ptr, data->win->win_ptr);
	if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY
									|| key == RIGHT_ARROW || key == LEFT_ARROW)
		ret = ft_movement_dispatch(data, key);
	else if (key >= NUMPAD_2 && key <= NUMPAD_8)
		ret = ft_standard_rotation(data, key);
	else if (key == ESC_KEY)
		ft_escape(data);
	return (ret);
}

