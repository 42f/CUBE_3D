/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:33:16 by bvalette          #+#    #+#             */
/*   Updated: 2020/05/28 15:51:51 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_keys.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*
** CONTROLE GAME EXPERIENCE DEFINES
*/

# define UNIT						64
# define MINIMAL_DIST				24
# define MOVEMENT_FACTOR			9
# define HUD_PATH_GUN_0				"./assets/HUD/GUN_0.xpm"
# define HUD_PATH_GUN_1				"./assets/HUD/GUN_1.xpm"
# define HUD_PATH_GUN_2				"./assets/HUD/GUN_2.xpm"
# define HUD_PATH_TARGET			"./assets/HUD/target.xpm"
# define HUD_PATH_LIFEBAR			"./assets/HUD/life_bar.xpm"

# ifndef MOUSE
#  define MOUSE						FALSE
# endif

# ifndef SHADOW
#  define SHADOW					FALSE
# endif

# ifndef SOLID_SPRITE
#  define SOLID_SPRITE				FALSE
# endif

/*
** img index define
*/

# define NO							0
# define SO							1
# define EA							2
# define WE							3
# define SP							4

# define GUN_0 						5
# define GUN_1 						6
# define GUN_2 						7
# define TARGET						8
# define LIFEBAR					9

# define VIEW						10

# define NBR_OF_USER_DEFINED_XPM	5
# define NBR_OF_XPM					10
# define NBR_OF_IMAGES				11

/*
** boolean defines
*/

# define FALSE						0
# define SUCCESS					1
# define TRUE						1

/*
** errors defines
*/

# define ERROR						-1
# define ERROR_MALLOC				-2
# define ERROR_MALLOC_IM			-3
# define ERROR_MLX					-4
# define ERROR_EXPORT				-5
# define ERROR_FILE					-6
# define ERROR_MAP					-7
# define ERROR_TEXTURE				-8
# define ERROR_PLAYER				-9
# define ERROR_TEXTURE_IMPORT		-10

/*
** colors defines
*/

# define BLUE						0x000000FF
# define GREEN						0x0000FF00
# define RED						0x00FF0000
# define WHITE						0x00FFFFFF

/*
** objects flags for ft_vertical and ft_horizontal
*/

# define EMPTY						0
# define WALL						1
# define SPRITE						2
# define V_WALL						3
# define H_WALL						4
# define V_SPRITE					5
# define H_SPRITE					6

/*
** color parser flags
*/

# define FLOOR						0
# define CEILING					1

/*
**	BMP export typedefs
*/

typedef struct	s_bmpheader
{
	short		bftype;
	int			bfsize;
	short		bfreserved1;
	short		bfreserved2;
	int			bfoffbits;
}				t_bmpheader;

typedef struct	s_bmpinfo
{
	int			bisize;
	int			biwidth;
	int			biheight;
	short		biplanes;
	short		bibitcount;
	int			bicompression;
	int			bisizeimage;
	int			bixpelspermeter;
	int			biypelspermeter;
	int			biclrused;
	int			biclrimportant;
}				t_bmpinfo;

/*
**	usefull typedef for cub3d
*/

typedef	struct	s_rgb_int
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_rgb_int;

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

typedef	struct	s_ints
{
	int			x;
	int			y;
}				t_ints;

/*
**	t_data members
*/

typedef struct	s_res
{
	double		x;
	double		y;
}				t_res;

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

typedef struct	s_files
{
	char		*cub_path;
	char		*xpm_path[NBR_OF_XPM];
}				t_files;

typedef struct	s_colors
{
	t_rgb_int	f_color_rgb;
	int			f_color;
	t_rgb_int	c_color_rgb;
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
	int			fire;
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
	short		export_flag;
	short		game_started;
}				t_data;

/*
** PARSER
*/

int				ft_parser(t_data *data);
int				ft_check_data(t_data *data);
int				ft_map_parser(t_data *data, int fd);
int				ft_map_checker(t_data *data);
int				**ft_init_grid(int x, int y);
int				ft_textures_parser(char *str, t_data *data);
int				ft_is_mapdata(char *line);
int				ft_is_onlyspaces(char *line);
int				ft_locate_all_sprites(t_data *data);
int				ft_resolution_parser(char *str, t_data *data);
int				ft_check_file_extension(t_data *data);
void			ft_img_struct_init(t_data *data);

/*
** USER INTERACTIONS
*/

int				ft_movement_dispatch(t_data *data, int key);
int				ft_key_hook(int key, t_data *data);
int				ft_key_release_hook(int key, t_data *data);
int				ft_mouse_manager(int x, int y, void *param);
int				ft_escape(t_data *data);

/*
** RENDERING SPRITE
*/

void			ft_compute_sp_dist(t_data *data);
void			ft_sort_sp_dist(t_data *data);
void			ft_set_sp_index_len(t_data *data);
void			ft_init_sp(t_data *data);
void			ft_update_sp_data(t_data *data, double alpha,
												int index, t_intersect inter);
void			ft_get_cell_center(t_intersect *inter);
int				ft_render_sprite(t_data *data);
void			ft_render_visible_sp(t_data *data);

/*
** RENDERING VIEW
*/

int				ft_cub3d(t_data *data);
void			ft_put_images_view(t_data *data);
void			ft_render_bg(t_data *data, int x, int y_wallstart,
																int y_wallend);
int				ft_import_textures(t_data *data);

void			ft_draw_map(t_data *data);
int				ft_get_shade(double dist);
int				ft_add_shade(t_data *data, int color, double y);

/*
** RENDER_UTILS
*/

int				ft_render_view(t_data *data);
t_intersect		ft_find_wall(t_data *data, double alpha);
t_intersect		ft_wall_vertical(t_data *data, double alpha_deg);
t_intersect		ft_wall_horizontal(t_data *data, double alpha_deg);
t_intersect		ft_sp_vertical(t_data *data, double alpha_deg, t_coord origin);
t_intersect		ft_sp_horizontal(t_data *data, double alpha_deg,
																t_coord origin);
int				ft_intersect_orientation(double alpha, int orientation_flag);
double			ft_map_alpha(double alpha);
double			ft_convert_alpha(double alpha_deg);

/*
** UTILS
*/

int				ft_col_conv(t_data *data, int r, int g, int b);
int				ft_save_to_file(t_data *data);
int				ft_cell_type(t_data *data, t_coord in,
													double alpha_deg, int flag);
void			ft_imgset(int *img, int color, size_t len);
int				ft_pos(int x, int y, int size_line);
double			ft_torad(double x);
void			ft_free_sprites(t_data *data, int i);
void			ft_free_grid(t_data *data, int **grid);
int				ft_free_all(t_data *data, int ret);
void			ft_print_error(t_data *data, int ret);

/*
** DEBUG
*/

void			debug_print_spdata(t_data *data);
void			debug_printgrid(t_data *data, int **map);
void			debug_printdata(t_data *data, int ret);
void			debug_checkgrid(double x, double y, t_data *data, int factor);
#endif
