#!/bin/bash
reset
printf "\033[0;32m\n\n[STARTING] test with valid maps and cub files...\n\n\n\n"

printf "\033[0;32m\n Next : Valid map... no shadow, no solid sprites\033[0m\n"
(set -x; make re SHADOW=0 SOLID_SPRITE=0 && ./cub3D maps/VALID_map.cub)

printf "\033[0;32m\n Next : Valid map...with shadow, with solid sprites\033[0m\n"
(set -x; make re SHADOW=1 SOLID_SPRITE=1 && ./cub3D maps/VALID_map.cub)

printf "\033[0;32m\n Next : /KO_too_high_resolution.cub = Resolution is 4000x4000\033[0m\n"
(set -x; ./cub3D maps/KO_too_high_resolution.cub)

printf "\033[0;32m\n Next : Valid map... With export flag on : See export.bmp\033[0m\n"
(set -x; ./cub3D maps/VALID_map.cub --save)
