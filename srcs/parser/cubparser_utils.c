/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubparser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 09:28:51 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/03 15:08:48 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int		ft_is_mapdata(char *line)
{
	int		i;
	int		y;
	char	*set;

	if (ft_strlen(line) == 0)
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


