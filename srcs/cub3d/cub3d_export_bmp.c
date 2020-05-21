/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_export_bmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 17:14:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 10:39:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

static int		ft_copy_img(t_data *data, int fd)
{
	int			x;
	int			y;
	int			cursor;
	int			ret;
	int			color;

	ret = TRUE;
	x = 0;
	y = data->res->y - 1;
	while (y >= 0)
	{
		while (x < data->res->x && ret != ERROR)
		{
			cursor = ft_pos(x, y, data->img[VIEW]->size_line);
			color = data->img[VIEW]->data[cursor];
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

static int		ft_write_header(t_bmpheader *head, t_bmpinfo *info, int fd)
{
	int			ret;

	ret = 0;
	ret += write(fd, &head->bfType, sizeof(short));
	ret += write(fd, &head->bfSize, sizeof(int));
	ret += write(fd, &head->bfReserved1, sizeof(short));
	ret += write(fd, &head->bfReserved2, sizeof(short));
	ret += write(fd, &head->bfOffBits, sizeof(int));
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

static void		ft_init_header(t_data *data, t_bmpheader *head, t_bmpinfo *info)
{
	int			bpp;

	bpp = data->img[VIEW]->bpp;
	head->bfType = 0x4d42;
	head->bfReserved1 = 0;
	head->bfReserved2 = 0;
	head->bfOffBits = sizeof(int) * 11 + sizeof(short) * 5;
	head->bfSize = head->bfOffBits;
	head->bfSize += data->res->x * data->res->y * (bpp);
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

int				ft_save_to_file(t_data *data)
{
	int			ret;
	int			fd;
	t_bmpinfo	info;
	t_bmpheader	head;

	ret = TRUE;
	fd = open("./export.bmp", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != ERROR)
	{
		ft_init_header(data, &head, &info);
		ret = ft_write_header(&head, &info, fd);
		if (ret == TRUE)
			ret = ft_copy_img(data, fd);
		close(fd);
	}
	return (ret);
}
