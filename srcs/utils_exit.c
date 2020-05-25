/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:47:28 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/25 12:29:10 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void		ft_free_grid(t_data *data, int **grid)
{
	int		i;

	i = 0;
	while (i < data->map->y)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void		ft_free_sprites(t_data *data, int i)
{
	while (i >= 0)
	{
		free(data->map->sp[i]);
		i--;
	}
	free(data->map->sp);
}

void		ft_free_textures(t_data *data)
{
	int	flag;

	flag = 0;
	if (data->win->win_ptr != NULL)
	{
		while (flag <= VIEW)
			free(data->img[flag++]);
	}
}

static void	ft_free_all_end(t_data *data, int ret)
{
	int	i;

	i = 0;
	if (ret == TRUE || ret == ERROR_EXPORT)
		ft_free_textures(data);
	if (data != NULL && data->map != NULL)
		ft_free_sprites(data, data->map->sp_qty - 1);
	if (data != NULL && data->files != NULL)
		while (i < NBR_OF_USER_DEFINED_XPM)
			free(data->files->xpm_path[i++]);
	if (data != NULL && data->map->grid != NULL)
		ft_free_grid(data, data->map->grid);
	if (data != NULL)
	{
		free(data->map);
		free(data->player);
		free(data->res);
		free(data->files);
		free(data->colors);
		free(data->win);
		free(data->img);
		free(data);
	}
}

int			ft_free_all(t_data *data, int ret)
{
	int	flag;

	ft_print_error(data, ret);
	if (ret != ERROR_MALLOC && ret != ERROR_FILE)
	{
		if (data != NULL && data->win->win_ptr != NULL)
		{
			flag = 0;
			while (ret != ERROR_TEXTURE_IMPORT && flag <= VIEW)
			{
				if (data->img[flag]->data != NULL)
					mlx_destroy_image(data->win->mlx_ptr, data->img[flag]->ptr);
				flag++;
			}
			if (data->export_flag == TRUE)
				free(data->win->mlx_ptr);
			else
				mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
		}
		ft_free_all_end(data, ret);
	}
	exit(ret);
}
