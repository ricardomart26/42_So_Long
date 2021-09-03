#include "../includes/so_long.h"

void	init_master(t_master *master)
{
	master->mlx = NULL;
	master->win = NULL;
	master->player_moves = 0;
	master->lives = 3;
}

void	init_map(t_map **map)
{
	*map = malloc(sizeof(t_map) + 1);
	(*map)->height = 0;
	(*map)->total = 0;
	(*map)->width = 0;
	(*map)->pos_x_y.x = 0;
	(*map)->pos_x_y.y = 0;
	(*map)->map2d = NULL;
}

void	init_parse_info(t_parse_info *info)
{
	info->c_exists = 0;
	info->e_exists = 0;
	info->p_exists = 0;
}
