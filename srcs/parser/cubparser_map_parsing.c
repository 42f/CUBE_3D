/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_map_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 09:00:54 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/17 20:12:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <stdlib.h>
#include <fcntl.h>

static void	ft_parse_line(t_data *data, char *line, int y)
{
	int		i;
	
	i = 0;
	if (y >= data->map->y)
	{
		data->map->set = ERROR_MAP;
		return ;
	}
	while (line != NULL && *line != '\0' && i < data->map->x)
	{
		if (*line == ' ')
			data->map->grid[y][i] = 0;
		else if (*line == '0' || *line == '1' || *line == '2')
			data->map->grid[y][i] = *line - 48;
		else if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			data->map->grid[y][i] = *line;
		else
			data->map->set = ERROR_MAP; 
		line++;
		i++;
	}
}

static int	ft_parse_grid(t_data *data)
{
	int		fd;
	int		ret_gnl;
	char	*line;
	int		y;

	y = 0;
	ret_gnl = TRUE;
	fd = open(data->files->cub_path, O_RDONLY);
	while (fd != ERROR && ret_gnl == TRUE)
	{
		ret_gnl = get_next_line(fd, &line);
		if (ret_gnl != ERROR && ft_is_mapdata(line) == TRUE) 
		{
			ft_parse_line(data, line, y);
			y++;
		}
		free(line);
	}
	close(fd);
	if (ret_gnl == ERROR)
		return (ERROR_FILE);
	data->map->set = TRUE;
	return (TRUE);
}

int			**ft_init_grid(int x, int y)
{
	int		i;
	int		**output;

	output = NULL;
	if (x > 0 && y > 0)
	{
		output = (int **)malloc(sizeof(int *) * y);
		i = 0;
		while (i < y && output != NULL)
		{
			output[i] = (int *)ft_calloc(sizeof(int), x);
			if (output[i] == NULL)
			{
				while (i >= 0)
					free(output[i--]);
				free(output);
				return (NULL);
			}
			i++;
		}
	}
	return (output);
}

int			ft_grid_calibrator(int fd, t_data *data)
{
	int		ret;
	int		ret_gnl;
	size_t	lines_nbr;
	size_t	max_len;
	char	*line;

	ret = TRUE;
	ret_gnl = TRUE;
	max_len = 0;
	lines_nbr = 1;
	while (ret_gnl == TRUE && ret == TRUE)
	{
		ret_gnl = get_next_line(fd, &line);
		if (ret_gnl != ERROR)
		{
			ret = ft_is_mapdata(line);
			lines_nbr++;
			max_len = (ft_strlen(line) > max_len) ? ft_strlen(line) : max_len;
		}
		free(line);
	}
	if (ret_gnl == ERROR || ret == ERROR)
		return (ERROR);
	data->map->x = max_len;
	data->map->y = lines_nbr;
	return (TRUE);
}

int		ft_map_parser(t_data *data, int fd)
{
	if (data->map->set == FALSE)
	{
		if (ft_grid_calibrator(fd, data) == ERROR)
			return (ERROR_MAP);
		data->map->grid = ft_init_grid(data->map->x, data->map->y);
		if (data->map->grid == NULL)
			return (ERROR_MALLOC);
		else		
			return (ft_parse_grid(data));
	}
	else
	{	
		data->map->set = ERROR;
		return (ERROR);
	}
}
