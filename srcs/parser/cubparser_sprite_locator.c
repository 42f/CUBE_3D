/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_sprite_locator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:41:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 10:55:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_locate_all_sprites(t_data *data)
{
	static t_ints	loc;
	static int		sp_index;

	while (loc.y < data->map->y)
	{
		while (loc.x < data->map->x)
		{
			if (data->map->grid[loc.y][loc.x] == 2)
			{
				if (!(data->map->sp[sp_index] = malloc(sizeof(t_sprite))))
				{
					ft_free_sprites(data, sp_index);
					return (ERROR_MALLOC);
				}
				data->map->sp[sp_index]->coord.x = (loc.x * UNIT) + (UNIT / 2);
				data->map->sp[sp_index]->coord.y = (loc.y * UNIT) + (UNIT / 2);
				data->map->sp[sp_index]->id = sp_index;
				sp_index++;
			}
			loc.x++;
		}
		loc.y++;
		loc.x = 0;
	}
	return (TRUE);
}
