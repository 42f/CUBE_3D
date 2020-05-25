#!/usr/bin/env zsh

reset && make
printf "\033[0;32m\n\n[STARTING]\n\n\n"

printf "\033[0;93m\n\n[NORMINETTE]\033[0m\n"
~/.norminette/norminette.rb srcs/*.c srcs/*/*.c includes/cub3d.h

printf "\033[0;93m\n\n[TESTING WRONG ARGUMENTS]\n"

printf "\033[0;32m NEXT : no argument\033[0m\n"
(set -x; ./cub3D)

printf "\033[0;32m NEXT : too many arguments\033[0m\n"
(set -x; ./cub3D maps/KO_extra_player_map.cub --save extra_arg)

printf "\033[0;32m NEXT : wrong flag\033[0m\n"
(set -x; ./cub3D maps/KO_extra_player_map.cub --wrong_flag)

printf "\033[0;93m\n [TESTING CUB FILES...]\033[0m\n"

printf "\033[0;32m NEXT : /KO_extra_player_map.cub = 2 players in the same map\033[0m\n"
./cub3D maps/KO_extra_player_map.cub

printf "\033[0;32m NEXT : /KO_missing_map.cub = no map at all\033[0m\n"
./cub3D maps/KO_missing_map.cub

printf "\033[0;32m NEXT : /KO_open_wall_map.cub = not closed map\033[0m\n"
./cub3D maps/KO_open_wall_map.cub

printf "\033[0;32m NEXT : /KO_no_player_map.cub = map with no player inside\033[0m\n"
./cub3D maps/KO_no_player_map.cub

printf "\033[0;32m NEXT : /KO_extra_map.cub = 2 maps\033[0m\n"
./cub3D maps/KO_extra_map.cub

printf "\033[0;32m NEXT : /KO_bad_char_in_map.cub = char in map which is different from 0 1 2 N S W E or space\033[0m\n"
./cub3D maps/KO_bad_char_in_map.cub

printf "\033[0;32m NEXT : /KO_bad_key.cub = extra key in list of textures\033[0m\n"
./cub3D maps/KO_bad_key.cub

printf "\033[0;32m NEXT : /KO_extra_texture.cub = 2 times the same texture key\033[0m\n"
./cub3D maps/KO_extra_texture.cub

printf "\033[0;32m NEXT : /KO_extra_resolution.cub = 2 different resolution keys\033[0m\n"
./cub3D maps/KO_extra_resolution.cub

printf "\033[0;32m NEXT : /KO_extra_color.cub = 1 extra ceiling color keys\033[0m\n"
./cub3D maps/KO_extra_color.cub

printf "\033[0;32m NEXT : /KO_missing_texture_file.cub = file path invalid for one texture\033[0m\n"
./cub3D maps/KO_missing_texture_file.cub

printf "\033[0;32m NEXT : /KO_missing_one_color.cub = no ceiling color\033[0m\n"
./cub3D maps/KO_missing_one_color.cub

printf "\033[0;32m NEXT : /KO_missing_one_texture.cub = only 3 textures keys\033[0m\n"
./cub3D maps/KO_missing_one_texture.cub

printf "\033[0;32m NEXT : /KO_no_cub_extension = file is correct, just missing the extention\n"
./cub3D maps/KO_no_cub_extension

printf "\033[0;32m NEXT : /KO_no_resolution.cub = missing the R key\033[0m\n"
./cub3D maps/KO_no_resolution.cub

