/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 08:57:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/16 17:34:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include "cub3d.h" 
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static void		ft_struct_values(t_data *data)
{
	data->win->mlx_ptr = NULL;
	data->win->win_ptr = NULL;
	data->files->no_path = NULL;
	data->files->sp_path = NULL;
	data->files->so_path = NULL;
	data->files->we_path = NULL;
	data->files->ea_path = NULL;
	data->map->set = FALSE;
	data->map->grid = NULL;
	data->map->sp = NULL;
	data->res->x = -1;
	data->res->y = -1;
	data->colors->f_color = -1;
	data->colors->c_color = -1;
	data->player->x = -1;
	data->player->y = -1;
}

static int		ft_struct_failure(t_data *data, int failure)
{
	if (failure > 0)
		free(data->win);
	if (failure > 1)
		free(data->res);
	if (failure > 2)
		free(data->colors);
	if (failure > 3)
		free(data->map);
	if (failure > 4)
		free(data->player);
	if (failure > 5)
		free(data->files);
	free(data);
	return (ERROR_MALLOC);
}

static int		ft_struct_init(t_data *data)
{
	data->win = malloc(sizeof(t_window));
	if (data->win == NULL)
		return (ft_struct_failure(data, 0));
	data->res = malloc(sizeof(t_res));
	if (data->res == NULL)
		return (ft_struct_failure(data, 1));
	data->colors = malloc(sizeof(t_colors));
	if (data->colors == NULL)
		return (ft_struct_failure(data, 2));
	data->map = malloc(sizeof(t_map));
	if (data->map == NULL)
		return (ft_struct_failure(data, 3));
	data->player = malloc(sizeof(t_player));
	if (data->player == NULL)
		return (ft_struct_failure(data, 4));
	data->files = malloc(sizeof(t_files));
	if (data->files == NULL)
		return (ft_struct_failure(data, 5));
	data->img = malloc(sizeof(t_img *) * 6);
	if (data->img == NULL)
		return (ft_struct_failure(data, 6));
	ft_struct_values(data);
	return (TRUE);
}

static int	ft_execute(t_data *data)
{
	int		ret;

	ret = ft_parser(data);
	if (ret == TRUE)
		ret = ft_cub3d(data);
	return (ret);
}

int 		main(int ac, char **av)
{
	int 	ret;
	t_data	*data;
	
	data = NULL;
	ret = FALSE;
	if (ac == 1 || ac > 3 || (ac == 3 && ft_memcmp(av[2], "--save", 6) != 0))
	{
		write(1, "\033[0;31mError\nUSAGE ./cub3d cub [--save] \033[0m\n\n", 46);
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		write(1, "\033[0;31mError\nMalloc failed              \033[0m\n\n", 46);
		return (0);
	}
	ret = ft_struct_init(data); 
	if (ret != TRUE)
	{
		write(1, "\033[0;31mError\nMalloc failed              \033[0m\n\n", 46);
		return (0);
	}
	data->files->cub_path = av[1];
	data->export_flag = (ac == 3);
	ret = ft_execute(data);
	return (ret);
}
