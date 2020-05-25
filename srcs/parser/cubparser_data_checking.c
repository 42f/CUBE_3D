/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_data_checking.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 08:54:11 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/25 15:38:42 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

int		ft_check_data(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (i < NBR_OF_XPM)
	{
		if (data->files->xpm_path[i] == NULL)
			return (ERROR);
		fd = open(data->files->xpm_path[i], O_RDONLY);
		if (fd == ERROR)
			return (ERROR_TEXTURE);
		close(fd);
		i++;
	}
	if (data->colors->f_color == -1 || data->colors->c_color == -1)
		return (ERROR);
	if (data->res->x < 1 || data->res->y < 1 || data->map->set != TRUE)
		return (ERROR);
	return (TRUE);
}
