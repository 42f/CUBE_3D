/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:33:16 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/15 18:34:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3d_H
# define CUB3d_H

// TO REMOVE -----------------
// TO REMOVE -----------------
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
// TO REMOVE -----------------
// TO REMOVE -----------------


#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
** screen resolution defines
*/
/*
#ifndef RES_X
# define RES_X 2560
#endif

#ifndef RES_Y
# define RES_Y 1440
#endif
*/

# define RES_X 2560
# define RES_Y 1440


/*
** boolean defines
*/

#define TRUE						1
#define FALSE						0

/*
** errors defines
*/

#define ERROR						-1
#define ERROR_FILE					-2
#define ERROR_MAP					-3
#define ERROR_MALLOC				-4
#define ERROR_MALLOC_IM				-5
#define ERROR_PLAYER				-6
#define ERROR_MLX					-7
#define ERROR_EXPORT				-8
#define ERROR_TEXTURE				-9
#define ERROR_TEXTURE_IMPORT		-10

/*
** keys for movements defines
*/

#define LEFT_ARROW					65361
#define RIGHT_ARROW					65363
#define NUMPAD_2					65433
#define NUMPAD_4					65430
#define NUMPAD_6					65432
#define NUMPAD_8					65431
#define A_KEY						97
#define S_KEY						115
#define D_KEY						100
#define W_KEY						119
#define M_KEY						109
#define ESC_KEY						65307

#define VERTICAL					1
#define HORIZONTAL					2

/*
** colors defines
*/

#define BLUE						0x000000FF
#define GREEN						0x0000FF00
#define RED							0x00FF0000
#define WHITE						0x00FFFFFF

/*
** miscellaneous defines
*/

#define UNIT						64	
#define MINIMAL_DIST				24	
#define MOVEMENT_FACTOR				9						
#define SHADOW						FALSE	
#define SHADOW_DEPTH				150
#define MOUSE						FALSE

/*
** img index define
*/

#define NO							0
#define SO							1
#define EA							2
#define WE							3
#define SP							4
#define SP_VIEW						5
#define VIEW						6
#define BG							7

/*
** objects flags for ft_vertical and ft_horizontal
*/

#define EMPTY						0
#define WALL						1
#define SPRITE						2
#define V_WALL						3
#define H_WALL						4
#define V_SPRITE					5
#define H_SPRITE					6


typedef struct		s_bmpheader
{
	short	bfType;
	int		bfSize;
	short	bfReserved1;
	short	bfReserved2;
	int		bfOffBits;
}					t_bmpheader;

typedef struct 		s_bmpinfo
{
	int		biSize;
	int		biWidth;
	int		biHeight;
	short	biPlanes;
	short	biBitCount;
	int		biCompression;
	int		biSizeImage;
	int		biXPelsPerMeter;
	int		biYPelsPerMeter;
	int		biClrUsed;
	int		biClrImportant;
} 					t_bmpinfo;

typedef	struct		s_RGB_int
{
	int		r;
	int		g;
	int		b;
	int		a;
}					t_RGB_int;

typedef struct	s_coordinates
{
	double		x;
	double		y;
}				t_coord;

typedef struct	s_intersect
{
	t_coord		coord;
	double		dist;
	double		height;
	int			flag;
}				t_intersect;

typedef struct	s_sprite
{
	t_coord		coord;
	double		dist;
	double		height;
	int			id;
	int			index_in;
	int			index_out;
	int			index_len;
}				t_sprite;

typedef	struct	s_ints
{
	int			x;
	int			y;
}				t_ints;

typedef struct	s_res
{
	double		x;
	double		y;
}				t_res;

/*
**	t_data members 
*/

typedef struct	s_files
{
	char		*cub_path;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*sp_path;
}				t_files;

typedef struct	s_colors
{
	int			f_color;
	int			c_color;
}				t_colors;

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			endian;
}				t_window;


typedef struct	s_map
{
	int			set;
	double		x;
	double		y;
	double		ratio_x;
	double		ratio_y;
	int			**grid;
	int			sp_qty;
	t_sprite	**sp;
}				t_map;

typedef struct	s_player
{
	double		x;
	double		y;
	double		a;
}				t_player;

typedef struct	s_img
{
	void		*ptr;
	int			width;
	int			height;
	int			size_line;
	int			bpp;
	int			*data;
}				t_img;

typedef struct	s_data
{
	t_window	*win;
	t_res		*res;
	t_colors	*colors;	
	t_map		*map;
	t_player	*player;
	t_files		*files;
	t_img		**img;
}				t_data;

/*
** PARSER
*/

int 			ft_parser(t_data *data);
int				ft_check_data(t_data *data);
int				ft_check_files(t_data *data);
void			ft_map_parser(t_data *data, int fd);
int				ft_map_checker(t_data *data);
int				**ft_init_grid(int x, int y);
int				ft_textures_parser(char *str, t_data *data);
int				ft_is_mapdata(char *line);

/*
** USER INTERACTIONS 
*/

int				ft_movement_dispatch(t_data *data, int key);
int				ft_key_manager(int key, void *param);
int				ft_mouse_manager(int x, int y, void *param);
int				ft_escape(t_data *data);

/*
** RENDERING 
*/

int				ft_cub3d(t_data *data, int export_flag);
int				ft_render_view(t_data *data);
void			ft_render_background(t_data *data);
int				ft_render_sprite(t_data *data);
int				ft_import_textures(t_data *data);

void			ft_draw_map(t_data *data);
int				ft_get_shade(double dist);

t_intersect		ft_find_wall(t_data *data, double alpha);
t_intersect		ft_wall_vertical(t_data *data, double alpha_deg);
t_intersect		ft_wall_horizontal(t_data *data, double alpha_deg);
t_intersect		ft_sp_vertical(t_data *data, int **map, double alpha_deg, t_coord origin);
t_intersect		ft_sp_horizontal(t_data *data, int **map, double alpha_deg, t_coord origin);


/*
** RENDER_UTILS 
*/

int				ft_intersect_orientation(double alpha, int orientation_flag);
double			ft_map_alpha(double alpha);
double			ft_convert_alpha(double alpha_deg);

/*
** UTILS 
*/

int				ft_col_conv(t_data *data, int r, int g, int b, int a);
int				ft_save_to_file(t_data *data);
int				ft_cell_type(t_data *data, int **map, t_coord in,
													double alpha_deg, int flag);
void			ft_imgset(int *img, int color, size_t len);
int				ft_pos(int x, int y, int size_line);
double			ft_torad(double x);
void			ft_free_sprites(t_data *data, int i);
void			ft_free_grid(t_data *data, int **grid);
int				ft_free_all(t_data *data, int ret);

/*
** DEBUG 
*/

void	debug_print_spdata(t_data *data);
void 	debug_printgrid(t_data *data, int **map);
void	debug_printdata(t_data *data, int ret);
void	debug_checkgrid(double x, double y, t_data *data, int factor);
#endif
