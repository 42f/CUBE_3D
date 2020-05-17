#!/bin/bash
clear && make DEBUG=1
printf "\033[0;32m\n\n[STARTING]...\n\n\n\n"

printf "\033[0;32m\n Next : /KO_bad_char_in_map.cub\033[0m\n"
./a.out maps/KO_bad_char_in_map.cub

printf "\033[0;32m\n Next : /KO_extra_map.cub\033[0m\n"
./a.out maps/KO_extra_map.cub

printf "\033[0;32m\n Next : /KO_bad_key.cub\033[0m\n"
./a.out maps/KO_bad_key.cub

printf "\033[0;32m\n Next : /KO_extra_player_map.cub\033[0m\n"
./a.out maps/KO_extra_player_map.cub

printf "\033[0;32m\n Next : /KO_extra_texture.cub\033[0m\n"
./a.out maps/KO_extra_texture.cub

printf "\033[0;32m\n Next : /KO_missing_texture_file.cub\033[0m\n"
./a.out maps/KO_missing_texture_file.cub

printf "\033[0;32m\n Next : /KO_missing_map.cub\033[0m\n"
./a.out maps/KO_missing_map.cub

printf "\033[0;32m\n Next : /KO_missing_one_color.cub\033[0m\n"
./a.out maps/KO_missing_one_color.cub

printf "\033[0;32m\n Next : /KO_missing_one_texture.cub\033[0m\n"
./a.out maps/KO_missing_one_texture.cub

printf "\033[0;32m\n Next : /KO_no_cub_extension\n"
./a.out maps/KO_no_cub_extension

printf "\033[0;32m\n Next : /KO_no_player_map.cub\033[0m\n"
./a.out maps/KO_no_player_map.cub

printf "\033[0;32m\n Next : /KO_no_resolution.cub\033[0m\n"
./a.out maps/KO_no_resolution.cub

printf "\033[0;32m\n Next : /KO_open_wall_map.cub\033[0m\n"
./a.out maps/KO_open_wall_map.cub

printf "\033[0;32m\n Next : /KO_too_high_resolution.cub\033[0m\n"
./a.out maps/KO_too_high_resolution.cub

printf "\033[0;32m\n Next : Valid map...\n"
./a.out maps/VALID_small_withsprites.cub
