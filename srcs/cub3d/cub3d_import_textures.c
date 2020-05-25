/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_import_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 09:45:14 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/24 23:52:16 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void ft_import_assets(t_data *data, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(data->win->mlx_ptr, path,
													&img->width, &img->height);
	if (img->ptr != NULL)
		img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
										&img->size_line, &data->win->endian);
}

static int	ft_failed_import(t_data *data, int flag)
{
	free(data->img[flag]);
	flag--;
	while (flag >= 0)
	{
		mlx_destroy_image(data->win->mlx_ptr, data->img[flag]->ptr);
		free(data->img[flag]);
		flag--;
	}
	return (ERROR_TEXTURE_IMPORT);
}

static void	ft_set_sizes(t_data *data, int flag)
{
	data->img[flag]->bpp /= 8;
	data->img[flag]->size_line /= data->img[flag]->bpp;
}

int			ft_import_textures(t_data *data)
{
	t_img		**img;
	char		*path[7];
	int			flag;
	
	img = data->img;
	path[NO] = data->files->no_path;
	path[SO] = data->files->so_path;
	path[EA] = data->files->ea_path;
	path[WE] = data->files->we_path;
	path[SP] = data->files->sp_path;
	path[GUN] = "./assets/gun/gun3.xpm";
	path[HUD] = "./assets/gun/HUD.xpm";
	flag = NO;
	while (flag <= HUD)
	{
		ft_import_assets(data, img[flag], path[flag]);
		if (img[flag]->ptr == NULL || img[flag]->data == NULL)
			return (ft_failed_import(data, flag));
		ft_set_sizes(data, flag);
		flag++;
	}
	return (TRUE);
}
