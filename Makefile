
CC			= clang

INC			= includes
LIBFT_DIR	:= ./libft/
LIBFT		:= $(LIBFT_DIR)libft.a
MLX_DIR		:= ./minilibx-Linux/
LIBMLX		:= $(MLX_DIR)libmlx.a

CFLAGS		+= -Wall
CFLAGS		+= -Werror
CFLAGS		+= -Wextra
CFLAGS		+= -g

ifeq ($(DEBUG), 1)
DEBUG_FLAGS		= -fsanitize=address
endif

ifeq ($(DEBUG_UNDEF), 1)
DEBUG_FLAGS		= -fsanitize=undefined
endif

NAME		= a.out

S_DIR 	= srcs

SRCS	= $(S_DIR)/debug_utils.c
SRCS	+= $(S_DIR)/main.c
SRCS	+= $(S_DIR)/utils_00.c
SRCS	+= $(S_DIR)/utils_exit.c
SRCS	+= $(S_DIR)/cub3d/cub3d.c
SRCS	+= $(S_DIR)/cub3d/cub3d_export_bmp.c
SRCS	+= $(S_DIR)/cub3d/cub3d_import_textures.c
SRCS	+= $(S_DIR)/cub3d/cub3d_key.c
SRCS	+= $(S_DIR)/cub3d/cub3d_key_mvmt.c
SRCS	+= $(S_DIR)/cub3d/cub3d_mouse_mvmt.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_utils.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_background.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_sprite_intersection.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_view.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_view_utils.c
SRCS	+= $(S_DIR)/cub3d/cub3d_render_wall_intersection.c
SRCS	+= $(S_DIR)/parser/cubparser.c
SRCS	+= $(S_DIR)/parser/cubparser_utils.c
SRCS	+= $(S_DIR)/parser/cubparser_data_checking.c
SRCS	+= $(S_DIR)/parser/cubparser_map_checking.c
SRCS	+= $(S_DIR)/parser/cubparser_map_parsing.c
SRCS	+= $(S_DIR)/parser/cubparser_textures.c

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
	$(CC) $(CFLAGS) -I $(INC) -o $@ -c $<

f: all
	./$(NAME) maps/VALID_simple_map.cub

cleancub:
	@echo "\n		🚧 cleaning objetcs of cub3d...\n"
	$(RM) $(OBJS)

clean:
	@echo "\n		🚧 cleaning objects of libft...\n"
	make clean -C $(LIBFT_DIR)
	@echo "\n		🚧 cleaning objetcs of cub3d...\n"
	$(RM) $(OBJS)

fclean: clean
	@echo "\n		🚧 forced cleaning libft...\n"
	make fclean -C $(LIBFT_DIR)
	@echo "\n		🚧 forced cleaning cub3d...\n"
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean re libft fclean objets f
