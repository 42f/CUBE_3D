/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:35:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/04/09 11:23:49 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

static int	ft_walls_textures(char type, char *str, t_data *data)
{
	if (type == 'N')
	{
		if (data->files->no_path != NULL)
			return (ERROR_TEXTURE);
		data->files->no_path = ft_strdup(str);
	}
	else if (type == 'S')
	{
		if (data->files->so_path != NULL)
			return (ERROR_TEXTURE);
	data->files->so_path = ft_strdup(str);
	}
	else if (type == 'W')
	{
		if (data->files->we_path != NULL)
			return (ERROR_TEXTURE);
		data->files->we_path = ft_strdup(str);
	}
	else if (type == 'E')
	{
		if (data->files->ea_path != NULL)
			return (ERROR_TEXTURE);
		data->files->ea_path = ft_strdup(str);
	}
	return (TRUE);
}

int			ft_textures_parser(char *str, t_data *data)
{
	char	type;
	int		ret;

	type = *str;
	if (ft_strncmp(str, "S ", 2) == 0)
	{
		str++;
		while (*str != '\0' && *str == ' ')
			str++;
		data->files->sp_path = ft_strdup(str);
		return (TRUE);
	}
	while (*str != '\0' && (ft_isalpha(*str)))
		str++;
	while (*str != '\0' && *str == ' ')
		str++;
	ret = ft_walls_textures(type, str, data);
	return (ret);
}

