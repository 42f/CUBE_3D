/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:13:10 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/24 20:01:53 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_standard_rotation(t_data *data, int key)
{
	if (key == NUMPAD_2)
		data->player->a = 270;
	else if (key == NUMPAD_4)
		data->player->a = 180;
	else if (key == NUMPAD_6)
		data->player->a = 0;
	else if (key == NUMPAD_8)
		data->player->a = 90;
}

int			ft_escape(t_data *data)
{
	ft_free_all(data, TRUE);
	return (TRUE);
}

int			ft_key_hook(int key, t_data *data)
{
	if (key == ESC_KEY)
		return (ft_escape(data));
	if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY
									|| key == RIGHT_ARROW || key == LEFT_ARROW)
		ft_movement_dispatch(data, key);
	else if (key >= NUMPAD_2 && key <= NUMPAD_8)
		ft_standard_rotation(data, key);
	else if (key == ESC_KEY)
		ft_escape(data);
	return (ft_render_view(data));
}
