

// do not push me !!

#include "libft.h"
#include "cub3d.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>


void		debug_checkgrid(double x, double y, t_data *data, int factor)
{
	int		new_x;
	int		new_y;
(void)factor;	
	
	if (x < 0 || x >= data->map->x)
		return ;
	if (y < 0 || y >= data->map->y)
		return ;
	new_x = floor(cos((M_PI * 0) / 180) + x);
	new_y = floor(sin((M_PI * 0) / 180) - y);
	printf("  0 = [%d]\n", data->map->grid[UNIT / new_y][UNIT / new_x]);
	new_x = floor(cos((M_PI * 90) / 180) + x);
	new_y = floor(sin((M_PI * 90) / 180) - y);
	printf(" 90 = [%d]\n", data->map->grid[UNIT / new_y][UNIT / new_x]);
	new_x = floor(cos((M_PI * 180) / 180) + x);
	new_y = floor(sin((M_PI * 180) / 180) - y);
	printf("180 = [%d]\n", data->map->grid[UNIT / new_y][UNIT / new_x]);
	new_x = floor(cos((M_PI * 270) / 180) + x);
	new_y = floor(sin((M_PI * 270) / 180) - y);
	printf("270 = [%d]\n", data->map->grid[UNIT / new_y][UNIT / new_x]);
	
}

void		debug_printdata(t_data *data, int ret)
{
	printf("____RETURN =____%d___________________________\n", ret);
	printf("data                         = %p\n", data);
	printf("address of data->map         = %p\n", data->map);
	printf("address of data->res         = %p\n", data->res);
	printf("address of data->file        = %p\n", data->files);
	printf("address of data->colors      = %p\n", data->colors);
	printf("address of data->win         = %p\n", data->win);
	printf("address of data->map         = %p\n", data->map);
	printf("data->res-x                = |%f|\n", data->res->x);
	printf("data->res-y                = |%f|\n", data->res->y);
	printf("data->files->sp_path   = |%s|\n", data->files->sp_path);
	printf("data->files->no_path   = |%s|\n", data->files->no_path);
	printf("data->files->so_path   = |%s|\n", data->files->so_path);
	printf("data->files->we_path   = |%s|\n", data->files->we_path);
	printf("data->files->ea_path   = |%s|\n", data->files->ea_path);
	printf("data->colors->floor        = |%d|\n", data->colors->f_color);
	printf("data->colors->ceiling      = |%d|\n", data->colors->c_color);
	printf("data->map->set             = |%d|\n", data->map->set);
	printf("data->map->x               = |%f|\n", data->map->x);
	printf("data->map->y               = |%f|\n", data->map->y);
	printf("data->map->grid address    = |%p|\n", data->map->grid);
	printf("data->player->x            = |%f|\n", data->player->x);
	printf("data->player->y            = |%f|\n", data->player->y);
	printf("data->player->a            = |%f|\n", data->player->a);
	printf("\n_________win_______\n");
	printf("data->win->mlx_ptr         = |%p|\n", data->win->mlx_ptr);
	printf("data->win->endian          = |%d|\n", data->win->endian);
	printf("data->map->sp_qty          = |%d|\n", data->map->sp_qty);
	debug_printgrid(data, data->map->grid);
}


void		debug_print_spdata(t_data *data)
{
	for (int i = 0; i < data->map->sp_qty; i++)
	{
		printf("data->map->sp[%3d] = [%4.0f, %4.0f] dist [%4.0f] index [%5d ~ %5d][%5d]", 
			data->map->sp[i]->id,
			data->map->sp[i]->coord.x,
			data->map->sp[i]->coord.y,
			data->map->sp[i]->dist,
			data->map->sp[i]->index_in,
			data->map->sp[i]->index_out,
			data->map->sp[i]->index_len
				);
		if ((data->map->sp[i]->index_in >= data->res->x && data->map->sp[i]->index_in <= data->res->x * 2)
		|| (data->map->sp[i]->index_in <= data->res->x * 2 && data->map->sp[i]->index_out > data->res->x * 2))
			printf("[visible]\n");
		else
			printf("\n");
		
	}
	printf("___________________\n\n");
}

void	debug_printgrid(t_data *data, int **map)
{	
	int i = 0;
	int j = 0;

	printf("address of grid = %p\n", map);	
	printf("x = %f, y = %f\n", data->map->x, data->map->y);	
	printf("%s\n", data->files->cub_path);

	if (data->map->set == ERROR)
		return ; 
	while (i < data->map->y)
	{
		while (j < data->map->x)
		{
//			if (map[i][j] < 10)
//				map[i][j] += 48;
			printf("%2d ", map[i][j]);
//			printf("%2c ", map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	printf("\n");
}
