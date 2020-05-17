#!/bin/bash
clear && make DEBUG=1
printf "\n\n[STARTING]...\n\n\n\n"

printf "\n Next : /KO_bad_char_in_map.cub\n"
./a.out maps/KO_bad_char_in_map.cub

printf "\n Next : /KO_extra_map.cub\n"
./a.out maps/KO_extra_map.cub

printf "\n Next : /KO_bad_key.cub\n"
./a.out maps/KO_bad_key.cub

printf "\n Next : /KO_extra_player_map.cub\n"
./a.out maps/KO_extra_player_map.cub

printf "\n Next : /KO_extra_texture.cub\n"
./a.out maps/KO_extra_texture.cub

printf "\n Next : /KO_missing_texture_file.cub\n"
./a.out maps/KO_missing_texture_file.cub

printf "\n Next : /KO_missing_map.cub\n"
./a.out maps/KO_missing_map.cub

: <<'END'
printf "\n Next : /KO_missing_one_color.cub\n"
./a.out maps/KO_missing_one_color.cub

printf "\n Next : /KO_missing_one_texture.cub\n"
./a.out maps/KO_missing_one_texture.cub

printf "\n Next : /KO_no_cub_extension\n"
./a.out maps/KO_no_cub_extension

printf "\n Next : /KO_no_player_map.cub\n"
./a.out maps/KO_no_player_map.cub

printf "\n Next : /KO_no_resolution.cub\n"
./a.out maps/KO_no_resolution.cub

printf "\n Next : /KO_open_wall_map.cub\n"
./a.out maps/KO_open_wall_map.cub

printf "\n Next : /KO_too_high_resolution.cub\n"
./a.out maps/KO_too_high_resolution.cub

printf "\n Next : Valid map...\n"
./a.out maps/VALID_small_withsprites.cub
END
