/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_cub3d_render_sprite.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 14:02:48 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/06 16:35:15 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

/*
static int	ft_get_pixel(t_data *data, double dist, int x, int y)
{
	int		cursor;
	
	y = (data->img[SP]->height / dist) * y;
	y = fmod(y ,data->img[SP]->height);
	cursor = (x + data->img[SP]->size_line * y);
	return(data->img[SP]->data[cursor]);
}

static void		ft_draw_column(t_data *data, int col, double dist, int x)
{
	static t_coord	coord;
	int				y_wallstart;
	int				y_wallend;
	int				color;
	int				cursor;

	y_wallstart = floor((data->res->y - dist) / 2);
	y_wallend = data->res->y - y_wallstart - 2;
	coord.y = y_wallstart;
	coord.x = x % data->img[SP]->width;
	while (coord.y < y_wallend)
	{
		color = ft_get_pixel(data, dist, coord.x, coord.y - y_wallstart);
//		color = RED;
		cursor = ft_pos(col, coord.y, data->img[SP_VIEW]->size_line, data);
		data->img[SP_VIEW]->data[cursor] = color;
		coord.y++;
	}
}



static t_sprite	*ft_locate_all_sprites(t_data *data, t_sprite *sp_array[])
{
	int			**grid_dup;
	int			i;
	double		alpha;

	grid_dup = NULL;
	grid_dup = ft_dup_map(data);	
	if (grid_dup == NULL)
		ft_free_all(data, ERROR_MLX);
	i = 0;
	alpha = 0;
	while (alpha >= 0)
	{
		alpha = ft_map_alpha(data->player->a + 90 - (60 / data->res->x * i));
//		sp.sprite = ft_find_intersection(data, alpha);
		i++;
	}
	ft_free_grid(data, grid_dup);
	return (*sp_array);
}
*/
/*
void		ft_render_sprite(t_data *data)
{
(void)data;
	//ft_locate_all_sprites(data, sp_array);
*/	
/*	int			i;
	double		alphat
	t_sprite	sp;
	double		dist;
	int			x;

	sp = (t_sprite){0, 0, 0, {0, 0, 0, 0}};
	ft_imgset(data->img[SP_VIEW]->data, 0xFF000000,
								data->img[SP_VIEW]->size_line * data->res->y);
	i = 0;
	sp.sprite = ft_find_intersection(data, sp.alpha_center);
	while (i < data->res->x)
	{
		alpha = (data->player->a + 30) - ((60 / data->res->x) * i);
		alpha = ft_map_alpha(alpha);
		dist = UNIT / sp.sprite.d * ((data->res->x / 2) / tan(ft_torad(30)));
		if (alpha <= sp.alpha1 && alpha >= sp.alpha2)
		{
			x =  floor(UNIT / (sp.alpha1 - sp.alpha2) * (sp.alpha1 - alpha));
			ft_draw_column(data, i, dist, x);
		}
		i++;
	}
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
												data->img[SP_VIEW]->ptr, 0, 0);
*/

}





/*
	printf("sp.alpha1 [%f], sp.alpha2 [%f], sp.alpha_center [%f], sp.sprite.x [%f], sp.sprite.y [%f], sp.sprite.d [%f], sp.sprite.flag [%d]\n\n", sp.alpha1, sp.alpha2, sp.alpha_center, sp.sprite.x, sp.sprite.y, sp.sprite.d, sp.sprite.flag);


		printf("[%.1f][%d]\n", alpha, sp.sprite.flag);
	printf("sp.alpha1 [%f], sp.alpha2 [%f], sp.alpha_center [%f], sp.sprite.x [%f], sp.sprite.y [%f], sp.sprite.d [%f], sp.sprite.flag [%d]\n\n", sp.alpha1, sp.alpha2, sp.alpha_center, sp.sprite.x, sp.sprite.y, sp.sprite.d, sp.sprite.flag);




*/
/*	if (sp.sprite.flag == EA)
			{
				sp.sprite.x += UNIT / 2;
				sp.sprite.y += UNIT / 2 - fmod(sp.sprite.y, UNIT);
			}	
			else if (sp.sprite.flag == WE)
			{
				sp.sprite.x -= UNIT / 2;
				sp.sprite.y += UNIT / 2 - fmod(sp.sprite.y, UNIT);
			}	
			else if (sp.sprite.flag == NO)
			{
				sp.sprite.x += UNIT / 2 - fmod(sp.sprite.x, UNIT);
				sp.sprite.y -= UNIT / 2;
			}	
			else if (sp.sprite.flag == SO)
			{
				sp.sprite.x += UNIT / 2 - fmod(sp.sprite.x, UNIT);
				sp.sprite.y += UNIT / 2;
			}
			sp.dist = fabs(fabs(data->player->y - sp.sprite.y) / cos(ft_torad(ft_convert_alpha(sp.alpha_center))));
		*/

