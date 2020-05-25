/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 15:35:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/25 12:27:01 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

static int	ft_get_walls_textures_paths(char type, char *str, t_data *data)
{
	char	*type_set;
	int		i;

	type_set = "NSEW";
	i = 0;
	while (i < 4 && type != type_set[i])
		i++;
	if (data->files->xpm_path[i] != NULL)
		return (ERROR_TEXTURE);
	data->files->xpm_path[i] = ft_strdup(str);
	return (TRUE);
}

int			ft_textures_parser(char *str, t_data *data)
{
	char	type;
	int		ret;

	ret = TRUE;
	type = *str;
	if (ft_strncmp(str, "S ", 2) == 0)
	{
		str++;
		while (*str != '\0' && *str == ' ')
			str++;
		data->files->xpm_path[SP] = ft_strdup(str);
	}
	else
	{
		while (*str != '\0' && (ft_isalpha(*str)))
			str++;
		while (*str != '\0' && *str == ' ')
			str++;
		ret = ft_get_walls_textures_paths(type, str, data);
	}
	return (ret);
}
