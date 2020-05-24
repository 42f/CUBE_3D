/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:25:21 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/24 20:05:58 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_struct_failure(t_data *data, int failure)
{
	if (failure > 0)
		free(data->img[SO]);
	if (failure > 1)
		free(data->img[NO]);
	if (failure > 2)
		free(data->img[EA]);
	if (failure > 3)
		free(data->img[WE]);
	if (failure > 4)
		free(data->img[SP]);
	if (failure > 5)
		free(data->img[GUN]);
	free(data->img);
	ft_free_all(data, ERROR_MALLOC_IM);
}

void		ft_img_struct_init(t_data *data)
{
	data->img[NO] = malloc(sizeof(t_img));
	if (data->img[NO] == NULL)
		ft_struct_failure(data, 0);
	data->img[SO] = malloc(sizeof(t_img));
	if (data->img[SO] == NULL)
		ft_struct_failure(data, 1);
	data->img[EA] = malloc(sizeof(t_img));
	if (data->img[EA] == NULL)
		ft_struct_failure(data, 2);
	data->img[WE] = malloc(sizeof(t_img));
	if (data->img[WE] == NULL)
		ft_struct_failure(data, 3);
	data->img[SP] = malloc(sizeof(t_img));
	if (data->img[SP] == NULL)
		ft_struct_failure(data, 4);
	data->img[GUN] = malloc(sizeof(t_img));
	if (data->img[GUN] == NULL)
		ft_struct_failure(data, 5);
	data->img[VIEW] = malloc(sizeof(t_img));
	if (data->img[VIEW] == NULL)
		ft_struct_failure(data, 6);
}
