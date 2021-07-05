
NAME		= cub3D

CC			= clang


LIBFT_DIR	:= ./libft

OS			:= $(shell uname -s)

ifeq ($(OS), Linux)
 INC			= includes_linux
 MLX_DIR	:= ./minilibx-linux/
 LIBFLAGS	+= -lbsd
 LIBFLAGS	+= -lX11 
 LIBFLAGS	+= -lXext 
 SRC		+= $(S_DIR)/cub3d/cub3d_mouse_mvmt_linux.c
else
 INC			= includes_macos
 MLX_DIR	:= ./minilibx-macos/
 LIBFLAGS	+= -framework OpenGL 
 LIBFLAGS	+= -framework AppKit
 LIBFLAGS	+= -lz
 SRC		+= $(S_DIR)/cub3d/cub3d_mouse_mvmt_macos.c
endif

LIBFT		:= $(LIBFT_DIR)/libft.a
LIBMLX		:= $(MLX_DIR)libmlx.a

HEADER		+=	$(LIBFT_DIR)/includes/libft.h
HEADER		+=	$(MLX_DIR)/mlx.h
HEADER		+=	$(INC)/cub3d.h

LIBFLAGS	+= -lm 

CFLAGS		+= -Wall
CFLAGS		+= -Werror
CFLAGS		+= -Wextra
CFLAGS		+= -O3

ifeq ($(SOLID_SPRITE), 1)
DEFINE_FLAGS		+= -D SOLID_SPRITE=1
endif

ifeq ($(SHADOW), 1)
DEFINE_FLAGS		+= -D SHADOW=1
endif

ifeq ($(DEBUG), 1)
DEBUG_FLAGS		= -fsanitize=address
endif

ifeq ($(DEBUG_UNDEF), 1)
DEBUG_FLAGS		= -fsanitize=undefined
endif

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
SRCS	+= $(S_DIR)/cub3d/cub3d_render_background.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_update.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_dist.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_intersection.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_draw.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_view.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_view_putimages.c
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

all:  $(NAME) 

FORCE:

$(LIBMLX): FORCE
	@make -C $(MLX_DIR)

$(LIBFT): FORCE
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) 
	@git submodule update --init --recursive			
	@echo "\n		🔗 Linking $@'s objects files...\n"
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS) $(LIBFLAGS) $(LIBMLX) $(LIBFT) -o $(NAME) 
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

norm	:	${SRCS} ${HEADER}
	OUTPUT = 	'~/.norminette/norminette.rb $(SRCS)'
	if ! echo "$OUTPUT" | grep -q "Error"; then	echo "STOP"

.PHONY: all clean re libft fclean objets lib_fclean lib_clean norm
