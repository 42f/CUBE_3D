#!/bin/bash
reset && make DEBUG=1
printf "\033[0;32m\n\n[STARTING] test with valid maps and cub files...\n\n\n\n"

printf "\033[0;32m\n Next : /KO_too_high_resolution.cub = Resolution is higher than the screen size\033[0m\n"
./Cub3D maps/KO_too_high_resolution.cub

printf "\033[0;32m\n Next : Valid map...\033[0m\n"
./Cub3D maps/VALID_small_withsprites.cub

printf "\033[0;32m\n Next : Valid map...\033[0m\n"
./Cub3D maps/VALID_small_withsprites.cub

