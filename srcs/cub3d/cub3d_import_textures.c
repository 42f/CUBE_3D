/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_import_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 09:45:14 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/17 23:19:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int			ft_import_textures(t_data *data)
{
	t_img		**img;
	char		*path[5];
	int			wall;

	img = data->img;
	path[NO] = data->files->no_path;
	path[SO] = data->files->so_path;
	path[EA] = data->files->ea_path;
	path[WE] = data->files->we_path;
	path[SP] = data->files->sp_path;
	wall = NO;
	while (wall <= SP)
	{
	/*	img[wall]->ptr = mlx_png_file_to_image(data->win->mlx_ptr,
							path[wall],	&img[wall]->width, &img[wall]->height);
		if (img[wall]->ptr == NULL)
	*/		img[wall]->ptr = mlx_xpm_file_to_image(data->win->mlx_ptr,
							path[wall], &img[wall]->width, &img[wall]->height);
		if (img[wall]->ptr != NULL)
			img[wall]->data = (int *)mlx_get_data_addr(img[wall]->ptr,
					&img[wall]->bpp, &img[wall]->size_line, &data->win->endian);
		if (img[wall]->ptr == NULL || img[wall]->data == NULL)
			return (ERROR_TEXTURE_IMPORT);
		img[wall]->bpp >>= 3;
		img[wall]->size_line /= img[wall]->bpp;
		wall++;
	}
	return (TRUE);
}
