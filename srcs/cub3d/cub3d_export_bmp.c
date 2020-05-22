/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_export_bmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 17:14:57 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/22 18:20:26 by bvalette         ###   ########.fr       */
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
	ret += write(fd, &head->bftype, sizeof(short));
	ret += write(fd, &head->bfsize, sizeof(int));
	ret += write(fd, &head->bfreserved1, sizeof(short));
	ret += write(fd, &head->bfreserved2, sizeof(short));
	ret += write(fd, &head->bfoffbits, sizeof(int));
	ret += write(fd, &info->bisize, sizeof(int));
	ret += write(fd, &info->biwidth, sizeof(int));
	ret += write(fd, &info->biheight, sizeof(int));
	ret += write(fd, &info->biplanes, sizeof(short));
	ret += write(fd, &info->bibitcount, sizeof(short));
	ret += write(fd, &info->bicompression, sizeof(int));
	ret += write(fd, &info->bisizeimage, sizeof(int));
	ret += write(fd, &info->bixpelspermeter, sizeof(int));
	ret += write(fd, &info->biypelspermeter, sizeof(int));
	ret += write(fd, &info->biclrused, sizeof(int));
	ret += write(fd, &info->biclrimportant, sizeof(int));
	if (ret != sizeof(int) * 11 + sizeof(short) * 5)
		return (ERROR_EXPORT);
	return (TRUE);
}

static void		ft_init_header(t_data *data, t_bmpheader *head, t_bmpinfo *info)
{
	int			bpp;

	bpp = data->img[VIEW]->bpp;
	head->bftype = 0x4d42;
	head->bfreserved1 = 0;
	head->bfreserved2 = 0;
	head->bfoffbits = sizeof(int) * 11 + sizeof(short) * 5;
	head->bfsize = head->bfoffbits;
	head->bfsize += data->res->x * data->res->y * (bpp);
	info->bisize = sizeof(int) * 9 + sizeof(short) * 2;
	info->biwidth = data->res->x;
	info->biheight = data->res->y;
	info->biplanes = 0x01;
	info->bibitcount = bpp * 8;
	info->bicompression = 0;
	info->bisizeimage = 0;
	info->bixpelspermeter = 0;
	info->biypelspermeter = 0;
	info->biclrused = 0;
	info->biclrimportant = 0;
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
