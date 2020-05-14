/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_export_bmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 17:14:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/10 14:46:55 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

static int		ft_get_pixel(t_data *data, int cursor)
{
	int				color_ret;
	unsigned int	c_background;
	unsigned int	c_walls;
	unsigned int	c_sprites;
	
	c_background = data->img[BG]->data[cursor];
	c_walls = data->img[VIEW]->data[cursor];
	c_sprites = data->img[SP_VIEW]->data[cursor];
	if (c_sprites != 0 && c_sprites != 0xFF000000)
		color_ret = c_sprites;
	else if (c_walls != 0 && c_walls != 0xFF000000)
		color_ret = c_walls;
	else
		color_ret = c_background;
	return (color_ret);
}

static int		ft_copy_img(t_data *data, int fd)
{
	int		x;
	int		y;
	int		cursor;
	int		ret;
	int		color;
	
	ret = TRUE;
	x = 0;
	y = data->res->y - 1;
	while (y >= 0)
	{
		while (x < data->res->x && ret != ERROR)
		{
			cursor = ft_pos(x, y, data->img[BG]->size_line);
			color = ft_get_pixel(data, cursor);
			ret = write(fd, &color, sizeof(int));
			x++;
		}
		x = 0;
		y--;
	}
	if (ret == ERROR)
		return (ERROR_EXPORT);
	return (TRUE);
}

static int		ft_write_header(t_bmpheader *header, t_bmpinfo *info, int fd)
{
	int		ret;

	ret = 0;
	ret += write(fd, &header->bfType, sizeof(short));
	ret += write(fd, &header->bfSize, sizeof(int));
	ret += write(fd, &header->bfReserved1, sizeof(short));
	ret += write(fd, &header->bfReserved2, sizeof(short));
	ret += write(fd, &header->bfOffBits, sizeof(int));
	ret += write(fd, &info->biSize, sizeof(int));
	ret += write(fd, &info->biWidth, sizeof(int));
	ret += write(fd, &info->biHeight, sizeof(int));
	ret += write(fd, &info->biPlanes, sizeof(short));
	ret += write(fd, &info->biBitCount, sizeof(short));
	ret += write(fd, &info->biCompression, sizeof(int));
	ret += write(fd, &info->biSizeImage, sizeof(int));
	ret += write(fd, &info->biXPelsPerMeter, sizeof(int));
	ret += write(fd, &info->biYPelsPerMeter, sizeof(int));
	ret += write(fd, &info->biClrUsed, sizeof(int));
	ret += write(fd, &info->biClrImportant, sizeof(int));
	if (ret != sizeof(int) * 11 + sizeof(short) * 5)
		return (ERROR_EXPORT);
	return (TRUE);
}

static void	ft_init_header(t_data *data, t_bmpheader *header, t_bmpinfo *info)
{
	int			bpp;

	bpp = data->img[VIEW]->bpp;
	header->bfType = 0x4d42;
	header->bfReserved1 = 0;
	header->bfReserved2 = 0;
	header->bfOffBits = sizeof(int) * 11 + sizeof(short) * 5;
	header->bfSize = header->bfOffBits;
	header->bfSize += data->res->x * data->res->y * (bpp); 
	info->biSize = sizeof(int) * 9 + sizeof(short) * 2; 
	info->biWidth = data->res->x;
	info->biHeight = data->res->y;
	info->biPlanes = 0x01;
	info->biBitCount = bpp * 8;
	info->biCompression = 0;
	info->biSizeImage = 0;
	info->biXPelsPerMeter = 0;
	info->biYPelsPerMeter = 0;
	info->biClrUsed = 0;
	info->biClrImportant = 0;
}

int			ft_save_to_file(t_data *data)
{
	int			ret;
	int			fd;
	t_bmpinfo	info;
	t_bmpheader	header;

	ret = TRUE;
	fd = open("./export.bmp", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != ERROR)
	{
		ft_init_header(data, &header, &info);
		ret = ft_write_header(&header, &info, fd);
		if (ret == TRUE)
			ret = ft_copy_img(data, fd);
		close(fd);
	}
	return (ret);
}
