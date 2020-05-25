/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:25:21 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/24 23:42:25 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	ft_struct_failure(t_data *data, int flag)
{
	flag--;
	while (flag >= 0)
	{
		free(data->img[flag]);
		flag--;
	}
	ft_free_all(data, ERROR_MALLOC_IM);
}

void		ft_img_struct_init(t_data *data)
{
	int	flag;

	flag = NO;
	while (flag <= VIEW)
	{
		data->img[flag] = malloc(sizeof(t_img));
		if (data->img[flag] == NULL)
			ft_struct_failure(data, flag);
		data->img[flag]->ptr = NULL;
		flag++;
	}
}
