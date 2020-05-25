/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_map_checking.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 07:41:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/25 12:45:36 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_ismapclosed(t_data *data, int x, int y, int **map)
{
	if (x == -1 || y == -1 || x == data->map->x || y == data->map->y)
		return (ERROR_MAP);
	if (data->map->grid[y][x] != 1 && map[y][x] != 1 && map[y][x] != -1)
	{
		map[y][x] = 1;
		if (ft_ismapclosed(data, x + 1, y, map) == ERROR_MAP)
			return (ERROR_MAP);
		if (ft_ismapclosed(data, x, y + 1, map) == ERROR_MAP)
			return (ERROR_MAP);
		if (ft_ismapclosed(data, x, y - 1, map) == ERROR_MAP)
			return (ERROR_MAP);
		if (ft_ismapclosed(data, x - 1, y, map) == ERROR_MAP)
			return (ERROR_MAP);
		map[y][x] = -1;
	}
	return (TRUE);
}

static int	ft_player_set(int x, int y, t_data *data, char orientation)
{
	if (data->player->x != -1 || data->player->y != -1)
		return (ERROR_PLAYER);
	data->player->a = (orientation == 'E') ? 0 : data->player->a;
	data->player->a = (orientation == 'N') ? 90 : data->player->a;
	data->player->a = (orientation == 'W') ? 180 : data->player->a;
	data->player->a = (orientation == 'S') ? 270 : data->player->a;
	data->player->x = (double)x;
	data->player->y = (double)y;
	data->player->sight_lever = 0;
	return (TRUE);
}

static int	ft_sp_and_player_locator(t_data *data)
{
	int		x;
	int		y;
	int		ret;

	x = 0;
	y = 0;
	ret = FALSE;
	data->map->sp_qty = 0;
	while (y < data->map->y && ret != ERROR_PLAYER)
	{
		while (x < data->map->x && ret != ERROR_PLAYER)
		{
			if (data->map->grid[y][x] == 'N' || data->map->grid[y][x] == 'S' ||
	data->map->grid[y][x] == 'W' || data->map->grid[y][x] == 'E')
				ret = ft_player_set(x, y, data, data->map->grid[y][x]);
			else if (data->map->grid[y][x] == 2)
				data->map->sp_qty++;
			x++;
		}
		y++;
		x = 0;
	}
	return (ret);
}

/*
** ft_map_padding put walls everywhere except where the player can move
*/

static void	ft_map_padding(t_data *data, int **map_dup)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < data->map->y)
	{
		while (x < data->map->x)
		{
			if (map_dup[y][x] == 0)
				data->map->grid[y][x] = 1;
			x++;
		}
		y++;
		x = 0;
	}
}

int			ft_map_checker(t_data *data)
{
	int		**map_dup;
	int		ret;

	ret = FALSE;
	ret = ft_sp_and_player_locator(data);
	if (ret == ERROR_PLAYER || ret == FALSE)
		return (ERROR_PLAYER);
	map_dup = NULL;
	map_dup = ft_init_grid(data->map->x, data->map->y);
	if (map_dup == NULL)
		return (ERROR_MALLOC);
	ret = ft_ismapclosed(data, data->player->x, data->player->y, map_dup);
	data->player->x = (data->player->x * UNIT) + (UNIT / 2);
	data->player->y = (data->player->y * UNIT) + (UNIT / 2);
	ft_map_padding(data, map_dup);
	ft_free_grid(data, map_dup);
	if (ret != TRUE)
		return (ERROR_MAP);
	data->map->sp = malloc(sizeof(t_sprite *) * data->map->sp_qty);
	if (data->map->sp == NULL)
		return (ERROR_MALLOC);
	ret = ft_locate_all_sprites(data);
	return (ret);
}
