/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_data_checking.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 08:54:11 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 10:14:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <stdlib.h>
#include <fcntl.h>

int		ft_check_files(t_data *data)
{
	int		fd;
	char	*files[5];
	int		i;

	files[0] = data->files->sp_path;
	files[1] = data->files->no_path;
	files[2] = data->files->so_path;
	files[3] = data->files->ea_path;
	files[4] = data->files->we_path;
	i = 0;
	while (i <= 4)
	{
		fd = open(files[i], O_RDONLY);
		if (fd == ERROR)
			return (ERROR_TEXTURE);
		close(fd);
		i++;
	}
	return (TRUE);
}

int		ft_check_data(t_data *data)
{
	if (data->map->set != TRUE)
		return (ERROR);
	if (data->files->sp_path == NULL)
		return (ERROR);
	if (data->files->no_path == NULL)
		return (ERROR);
	if (data->files->so_path == NULL)
		return (ERROR);
	if (data->files->ea_path == NULL)
		return (ERROR);
	if (data->files->we_path == NULL)
		return (ERROR);
	if (data->colors->f_color == -1 || data->colors->c_color == -1)
		return (ERROR);
	if (data->res->x < 1 || data->res->y < 1 || data->map->set != TRUE)
		return (ERROR);
	return (ft_check_files(data));
}
