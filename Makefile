
CC			= clang

INC			= includes
LIBFT_DIR	:= ./libft/
LIBFT		:= $(LIBFT_DIR)libft.a
MLX_DIR		:= ./minilibx-linux/
LIBMLX		:= $(MLX_DIR)libmlx.a

CFLAGS		+= -Wall
CFLAGS		+= -Werror
CFLAGS		+= -Wextra
CFLAGS		+= -g

ifeq ($(SOLID_SPRITE), 1)
DEFINE_FLAGS		+= -D SOLID_SPRITE=1
endif

ifeq ($(SOLID_SPRITE), 0)
DEFINE_FLAGS		+= -D SOLID_SPRITE=0
endif

ifeq ($(SHADOW), 1)
DEFINE_FLAGS		+= -D SHADOW=1
endif

ifeq ($(SHADOW), 0)
DEFINE_FLAGS		+= -D SHADOW=0
endif

ifeq ($(DEBUG), 1)
DEBUG_FLAGS		= -fsanitize=address
endif

ifeq ($(DEBUG_UNDEF), 1)
DEBUG_FLAGS		= -fsanitize=undefined
endif

NAME		= Cub3D

S_DIR 	= srcs

SRCS	+= $(S_DIR)/main.c
SRCS	+= $(S_DIR)/utils_00.c
SRCS	+= $(S_DIR)/utils_01.c
SRCS	+= $(S_DIR)/utils_exit.c
SRCS	+= $(S_DIR)/cub3d/cub3d.c
SRCS	+= $(S_DIR)/cub3d/cub3d_export_bmp.c
SRCS	+= $(S_DIR)/cub3d/cub3d_import_textures.c
SRCS	+= $(S_DIR)/cub3d/cub3d_key.c
SRCS	+= $(S_DIR)/cub3d/cub3d_key_mvmt.c
SRCS	+= $(S_DIR)/cub3d/cub3d_mouse_mvmt.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_background.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_update.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_dist.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_intersection.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_draw.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_view.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_view_utils.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_wall_intersection.c
SRCS	+= $(S_DIR)/cub3d/cub3d_struct.c
SRCS	+= $(S_DIR)/parser/cubparser.c
SRCS	+= $(S_DIR)/parser/cubparser_utils.c
SRCS	+= $(S_DIR)/parser/cubparser_data_checking.c
SRCS	+= $(S_DIR)/parser/cubparser_map_checking.c
SRCS	+= $(S_DIR)/parser/cubparser_map_parsing.c
SRCS	+= $(S_DIR)/parser/cubparser_textures.c
SRCS	+= $(S_DIR)/parser/cubparser_sprite_locator.c

OBJS	=	$(SRCS:.c=.o)

HEADER	=	$(INC)/libft.h
HEADER	+=	$(INC)/cub3d.h
HEADER	+=	$(INC)/mlx.h

all:  $(NAME) 

FORCE:

$(LIBMLX): FORCE
	@make -C $(MLX_DIR)

$(LIBFT): FORCE
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) 
	@echo "\n		🔗 Linking $@'s objects files...\n"
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS) -lm -lbsd -lX11 -lXext $(LIBMLX) $(LIBFT) -o $(NAME) 
	@echo "\n		🥳  Yay  !  $@ done.\n"
	@echo "Usage ./$@ cubfile_path [--save]\n"

$(OBJS): %.o : %.c $(HEADER) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(DEFINE_FLAGS) -I $(INC) -o $@ -c $<

lib_clean:
	@echo "\n		🚧 cleaning objects of libft...\n"
	make clean -C $(LIBFT_DIR)

clean:
	@echo "\n		🚧 cleaning objetcs of cub3d...\n"
	$(RM) $(OBJS)

lib_fclean:
	@echo "\n		🚧 forced cleaning libft...\n"
	make fclean -C $(LIBFT_DIR)

fclean: clean
	@echo "\n		🚧 forced cleaning cub3d...\n"
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean re libft fclean objets lib_fclean lib_clean
