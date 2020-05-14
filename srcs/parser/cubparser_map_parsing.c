/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_map_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 09:00:54 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/03 15:02:33 by bvalette         ###   ########.fr       */
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
	while (line != NULL && *line != '\0' && i < data->map->x)
	{
		if (*line == ' ')
			data->map->grid[y][i] = 0;
		else if (*line == '0' || *line == '1' || *line == '2')
			data->map->grid[y][i] = *line - 48;
		else if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			data->map->grid[y][i] = *line;
		line++;
		i++;
	}
}

static void	ft_parse_grid(t_data *data)
{
	int		fd;
	int		ret;
	char	*line;
	int		y;

	y = 0;
	ret = TRUE;
	fd = open(data->files->cub_path, O_RDONLY);
	while (ret == TRUE && fd != ERROR)
	{
		ret = get_next_line(fd, &line);
		if (ret != ERROR && ft_is_mapdata(line) == TRUE)
		{
			ft_parse_line(data, line, y);
			y++;
		}
		free(line);
	}
	close(fd);
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

void		ft_grid_calibrator(int fd, t_data *data)
{
	int		ret;
	size_t	lines_nbr;
	size_t	max_len;
	size_t	line_len;
	char	*line;

	ret = TRUE;
	max_len = 0;
	lines_nbr = 1;
	while (ret == TRUE && data->map->set != ERROR)
	{
		ret = get_next_line(fd, &line);
		if (ret != ERROR && ft_is_mapdata(line) == TRUE)
		{
			lines_nbr++;
			line_len = ft_strlen(line);
			max_len = (line_len > max_len) ? line_len : max_len;
			data->map->set = TRUE;
		}
		else if (ret == ERROR)
			data->map->set = ERROR;
		free(line);
	}
	data->map->x = max_len;
	data->map->y = lines_nbr;
}

void		ft_map_parser(t_data *data, int fd)
{
	if (data->map->set == FALSE)
	{
		ft_grid_calibrator(fd, data);
		if (data->map->set == ERROR)
			return ;
		if (data->map->set == TRUE)
		{
			data->map->grid = ft_init_grid(data->map->x, data->map->y);
			if (data->map->grid == NULL)
			{
				data->map->set = ERROR_MALLOC;
				return ;
			}
			ft_parse_grid(data);
		}
	}
	else
		data->map->set = ERROR_MAP;
}
