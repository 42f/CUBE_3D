/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 09:18:37 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/16 11:25:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

static void		ft_img_init(t_data *data)
{
	t_window	*win;
	t_res		res;
	
	win = data->win;
	res.x = data->res->x;
	res.y = data->res->y;
	data->img[SP_VIEW]->ptr = mlx_new_image(win->mlx_ptr, res.x, res.y);
	data->img[SP_VIEW]->data = (int *)mlx_get_data_addr(data->img[SP_VIEW]->ptr,
		&data->img[SP_VIEW]->bpp, &data->img[SP_VIEW]->size_line, &win->endian);
	data->img[SP_VIEW]->bpp /= 8;
	data->img[SP_VIEW]->size_line /= data->img[SP_VIEW]->bpp;
	data->img[VIEW]->ptr = mlx_new_image(win->mlx_ptr, res.x, res.y);
	data->img[VIEW]->data = (int *)mlx_get_data_addr(data->img[VIEW]->ptr,
			&data->img[VIEW]->bpp, &data->img[VIEW]->size_line, &win->endian);
	data->img[VIEW]->bpp /= 8;
	data->img[VIEW]->size_line /= data->img[VIEW]->bpp;
	data->img[BG]->ptr = mlx_new_image(win->mlx_ptr, res.x, res.y);
	data->img[BG]->data = (int *)mlx_get_data_addr(data->img[BG]->ptr,
			&data->img[BG]->bpp, &data->img[BG]->size_line, &win->endian);
	data->img[BG]->bpp /= 8;
	data->img[BG]->size_line /= data->img[BG]->bpp;
}

static void		ft_struct_failure(t_data *data, int failure)
{
	if (failure > 0)
		free(data->img[SO]);
	if (failure > 1)
		free(data->img[NO]);
	if (failure > 2)
		free(data->img[EA]);
	if (failure > 3)
		free(data->img[WE]);
	if (failure > 4)
		free(data->img[SP]);
	if (failure > 5)
		free(data->img[VIEW]);
	if (failure > 6)
		free(data->img[SP_VIEW]);
	free(data->img);
	ft_free_all(data, ERROR_MALLOC_IM);
}

static void		ft_img_struct_init(t_data *data)
{
	data->img[NO] = malloc(sizeof(t_img));
	if (data->img[NO] == NULL)
		ft_struct_failure(data, 0);
	data->img[SO] = malloc(sizeof(t_img));
	if (data->img[SO] == NULL)
		ft_struct_failure(data, 1);
	data->img[EA] = malloc(sizeof(t_img));
	if (data->img[EA] == NULL)
		ft_struct_failure(data, 2);
	data->img[WE] = malloc(sizeof(t_img));
	if (data->img[WE] == NULL)
		ft_struct_failure(data, 3);
	data->img[SP] = malloc(sizeof(t_img));
	if (data->img[SP] == NULL)
		ft_struct_failure(data, 4);
	data->img[VIEW] = malloc(sizeof(t_img));
	if (data->img[VIEW] == NULL)
		ft_struct_failure(data, 5);
	data->img[SP_VIEW] = malloc(sizeof(t_img));
	if (data->img[SP_VIEW] == NULL)
		ft_struct_failure(data, 6);
	data->img[BG] = malloc(sizeof(t_img));
	if (data->img[BG] == NULL)
		ft_struct_failure(data, 7);
}

static int		ft_mlx_init(t_data *data)
{
	t_res			res;
	t_window		*win;

	win = data->win;
	res.x = data->res->x;
	res.y = data->res->y;
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
		return (ERROR_MLX);
	win->win_ptr = mlx_new_window(win->mlx_ptr, res.x, res.y, "Cub3d");
	if (win->win_ptr == NULL)
		return (ERROR_MLX);
//	mlx_loop_hook(win->mlx_ptr, ft_render_view, data);
	mlx_hook(win->win_ptr, 6, (1L<<0), ft_mouse_manager, data);
	mlx_hook(win->win_ptr, 2, (1L<<0), ft_key_manager, data);
	mlx_hook(win->win_ptr, 17, (1L<<2), ft_escape, data);
	return (TRUE);
}

int		ft_cub3d(t_data *data, int export_flag)
{
	int			ret;
	
	ft_img_struct_init(data);
	ret = ft_mlx_init(data);
	if (ret != TRUE)
		return (ERROR_MLX);
	ft_img_init(data);
	ret = ft_import_textures(data);
	if (ret != TRUE)
		return (ret);

	// attention : utiliser ecran accueil PRESS KEY TO START pour eviter de gerer le return de render_view ici
	//mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, data->res->x / 2 - 70, data->res->y / 2, RED, "Press key to start");
//	debug_printdata(data, 8);
	mlx_do_key_autorepeaton(data->win->mlx_ptr);
	ft_render_view(data);
	if (export_flag == TRUE)
		ret = ft_save_to_file(data);
	else
		mlx_loop(data->win->mlx_ptr);
	return (ret);
}
