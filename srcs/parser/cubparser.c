/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 10:32:56 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/25 15:36:56 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

static void		ft_colors_set(t_data *data, int flag, t_rgb_int col)
{
	if (flag == FLOOR)
	{
		ft_memcpy(&data->colors->f_color_rgb, &col, sizeof(int) * 3);
		data->colors->f_color = TRUE;
	}
	else if (flag == CEILING)
	{
		ft_memcpy(&data->colors->c_color_rgb, &col, sizeof(int) * 3);
		data->colors->c_color = TRUE;
	}
}

static int		ft_colors_parser(char *str, t_data *data)
{
	t_rgb_int	col;
	char		type;

	type = *str;
	str++;
	if (data->colors->c_color == TRUE && data->colors->f_color == TRUE)
		return (ERROR_FILE);
	while (*str != '\0' && *str == ' ')
		str++;
	col.r = ft_atoi(str);
	while (*str != '\0' && (ft_isdigit(*str) == TRUE || *str == ' '))
		str++;
	str++;
	col.g = ft_atoi(str);
	while (*str != '\0' && (ft_isdigit(*str) == TRUE || *str == ' '))
		str++;
	str++;
	col.b = ft_atoi(str);
	while (ft_isdigit(*str) == TRUE || *str == ' ')
		str++;
	if (type == 'F' && col.r < 256 && col.g < 256 && col.b < 256)
		ft_colors_set(data, FLOOR, col);
	else if (type == 'C' && col.r < 256 && col.g < 256 && col.b < 256)
		ft_colors_set(data, CEILING, col);
	return (TRUE);
}

static int		ft_dispatch_parser(char *str, t_data *data)
{
	int		ret;

	ret = TRUE;
	if (ft_strncmp(str, "NO ", 3) == 0)
		ret = ft_textures_parser(str, data);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		ret = ft_textures_parser(str, data);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		ret = ft_textures_parser(str, data);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		ret = ft_textures_parser(str, data);
	else if (ft_strncmp(str, "S ", 2) == 0)
		ret = ft_textures_parser(str, data);
	else if (ft_strncmp(str, "R ", 2) == 0)
		ret = ft_resolution_parser(str, data);
	else if (ft_strncmp(str, "F ", 2) == 0)
		ret = ft_colors_parser(str, data);
	else if (ft_strncmp(str, "C ", 2) == 0)
		ret = ft_colors_parser(str, data);
	else
		ret = ERROR_FILE;
	return (ret);
}

static int		ft_read_file(t_data *data, int fd)
{
	int		ret_gnl;
	int		ret;
	char	*line;

	ret = TRUE;
	ret_gnl = TRUE;
	while (ret_gnl == TRUE && ret == TRUE)
	{
		ret_gnl = get_next_line(fd, &line);
		if (ret_gnl != ERROR)
		{
			if (ft_is_mapdata(line) == TRUE)
				ret = ft_map_parser(data, fd);
			else if (ft_is_onlyspaces(line) == FALSE)
				ret = ft_dispatch_parser(line, data);
		}
		free(line);
	}
	close(fd);
	if (ret_gnl == ERROR)
		ret = ERROR_FILE;
	return (ret);
}

int				ft_parser(t_data *data)
{
	int		ret;
	int		fd;

	ret = TRUE;
	fd = open(data->files->cub_path, O_RDONLY);
	if (fd == ERROR || ft_check_file_extension(data) == ERROR)
		return (ft_free_all(data, ERROR_FILE));
	ret = ft_read_file(data, fd);
	if (ret <= ERROR)
		return (ft_free_all(data, ret));
	else if (data->map->set == FALSE || data->map->set == ERROR)
		return (ft_free_all(data, ERROR_MAP));
	ret = ft_check_data(data);
	if (ret <= ERROR || data->map->set == FALSE || data->map->set == ERROR)
		return (ft_free_all(data, ret));
	ret = ft_map_checker(data);
	if (ret <= ERROR || data->map->set == FALSE || data->map->set == ERROR)
		return (ft_free_all(data, ret));
	return (TRUE);
}
