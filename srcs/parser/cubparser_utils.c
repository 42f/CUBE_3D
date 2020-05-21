/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 09:28:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/21 11:26:34 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int		ft_is_onlyspaces(char *line)
{
	while (*line != '\0' && *line == ' ')
		line++;
	if (*line == '\0')
		return (TRUE);
	else
		return (FALSE);
}

int		ft_is_mapdata(char *line)
{
	int		i;
	int		y;
	char	*set;

	if (ft_strlen(line) == 0 || ft_is_onlyspaces(line) == TRUE)
		return (FALSE);
	set = "012 NSEW";
	i = 0;
	y = 0;
	while (line[i] != '\0')
	{
		while (set[y] != '\0')
		{
			if (line[i] != set[y])
				y++;
			else
				break ;
		}
		if (set[y] == '\0')
			return (FALSE);
		y = 0;
		i++;
	}
	return (TRUE);
}

int		ft_resolution_parser(char *str, t_data *data)
{
	if (data->res->x != -1 || data->res->y != -1)
		return (ERROR_FILE);
	while (*str != '\0' && ft_isalpha(*str) == TRUE)
		str++;
	data->res->x = ft_atoi(str);
	while (*str != '\0' && *str == ' ')
		str++;
	while (*str != '\0' && ft_isdigit(*str) == TRUE)
		str++;
	data->res->y = ft_atoi(str);
	return (TRUE);
}

int		ft_check_file_extension(t_data *data)
{
	size_t len;

	len = ft_strlen(data->files->cub_path);
	if (len <= 4)
		return (ERROR);
	if (ft_memcmp(data->files->cub_path + (len - 4), ".cub", 4) != 0)
		return (ERROR);
	return (TRUE);
}
