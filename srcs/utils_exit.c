/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:47:28 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/18 20:28:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

void	ft_free_grid(t_data *data, int **grid)
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

static void	ft_print_error(t_data *data, int ret)
{
	if (ret == FALSE)
		write(1, "\033[0;31mError\nUSAGE ./cub3d cub [--save] \033[0m\n\n", 45);
	else if (ret == ERROR_MALLOC || ret == ERROR_MALLOC_IM)
		write(1, "\033[0;31mError\nMALLOC ERROR    \033[0m\n\n", 35);
	else if (ret == ERROR_TEXTURE_IMPORT)
		write(1, "\033[0;31mError\nCAN'T IMPORT TEXTURE  \033[0m\n\n", 40);
	else if (ret == ERROR_MAP)
		write(1, "\033[0;31mError\nMAP NOT CORRECT \033[0m\n\n", 35);
	else if (ret == ERROR_PLAYER)
		write(1, "\033[0;31mError\nPLAYER ERROR    \033[0m\n\n", 35);
	else if (data->map->set == ERROR)
		write(1, "\033[0;31mError\nMAP ERROR IN CUB\033[0m\n\n", 35);
	else if (data->map->set == ERROR_MALLOC)
		write(1, "\033[0;31mError\nMALLOC ERROR    \033[0m\n\n", 35);
	else if (ret == ERROR_MLX)
		write(1, "\033[0;31mError\nISSUE WITH MLX  \033[0m\n\n", 35);
	else if (ret == ERROR_FILE)
		write(1, "\033[0;31mError\nWRONG CUB  FILE \033[0m\n\n", 35);
	else if (ret == ERROR_TEXTURE)
		write(1, "\033[0;31mError\nISSUE W/ TEXTURE\033[0m\n\n", 35);
	else if (ret == ERROR_EXPORT)
		write(1, "\033[0;31mError\nCOULD NOT EXPORT\033[0m\n\n", 35);
	else if (ret != TRUE)
		write(1, "\033[0;31mError\nCUB FILE FAULTY \033[0m\n\n", 35);
}

void	ft_free_sprites(t_data *data, int i)
{
	while (i >= 0)
	{
	printf("free [%d] %p \n\n", i, data->map->sp[i]);
		free(data->map->sp[i]);
		i--;
	}
printf("MALLOC, add %p\n\n", data->map->sp);
	free(data->map->sp);
}

void	ft_free_textures(t_data *data)
{
	if (data->win->win_ptr != NULL)
	{
		free(data->img[NO]);
		free(data->img[SO]);
		free(data->img[EA]);
		free(data->img[WE]);
		free(data->img[SP]);
		free(data->img[GUN]);
		free(data->img[VIEW]);
	}
}

int		ft_free_all(t_data *data, int ret)
{
//	debug_printdata(data, ret);
//	data->img[10000]->data[0] = 1;
	ft_print_error(data, ret);
	if (ret != ERROR_MALLOC && ret != ERROR_FILE)
	{
		if (data != NULL && data->win->win_ptr != NULL)
		{	
			mlx_destroy_image(data->win->mlx_ptr, data->img[NO]->ptr);
			mlx_destroy_image(data->win->mlx_ptr, data->img[SO]->ptr);
			mlx_destroy_image(data->win->mlx_ptr, data->img[EA]->ptr);
			mlx_destroy_image(data->win->mlx_ptr, data->img[WE]->ptr);
			mlx_destroy_image(data->win->mlx_ptr, data->img[SP]->ptr);
			mlx_destroy_image(data->win->mlx_ptr, data->img[GUN]->ptr);
			mlx_destroy_image(data->win->mlx_ptr, data->img[VIEW]->ptr);
			if (data->export_flag == TRUE)
				free(data->win->mlx_ptr);
			else
				mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
		}
		if (ret == TRUE || ret == ERROR_EXPORT)
			ft_free_textures(data);
		if (data != NULL && data->map != NULL)
			ft_free_sprites(data, data->map->sp_qty - 1);
		if (data != NULL && data->files != NULL)
		{
			free(data->files->sp_path);
			free(data->files->no_path);
			free(data->files->we_path);
			free(data->files->ea_path);
			free(data->files->so_path);
		}
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
	exit (ret);
}

