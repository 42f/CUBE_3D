/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_import_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 09:45:14 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/20 17:51:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	ft_set_sizes(t_data *data, int flag)
{
	data->img[flag]->bpp /= 8;
	data->img[flag]->size_line /= data->img[flag]->bpp;
}

int			ft_import_textures(t_data *data)
{
	t_img		**img;
	char		*path[6];
	int			flag;

	img = data->img;
	path[NO] = data->files->no_path;
	path[SO] = data->files->so_path;
	path[EA] = data->files->ea_path;
	path[WE] = data->files->we_path;
	path[SP] = data->files->sp_path;
	path[GUN] = "./assets/gun/gun.xpm";
	flag = NO;
	while (flag <= GUN)
	{
		img[flag]->ptr = mlx_xpm_file_to_image(data->win->mlx_ptr,
							path[flag], &img[flag]->width, &img[flag]->height);
		if (img[flag]->ptr != NULL)
			img[flag]->data = (int *)mlx_get_data_addr(img[flag]->ptr,
					&img[flag]->bpp, &img[flag]->size_line, &data->win->endian);
		if (img[flag]->ptr == NULL || img[flag]->data == NULL)
			return (ERROR_TEXTURE_IMPORT);
		ft_set_sizes(data, flag);
		flag++;
	}
	return (TRUE);
}
