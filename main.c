#include "so_long.h"

void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->pos.player_x = 0;
	map->pos.player_y = 0;
	map->pos.collect_x = 0;
	map->pos.collect_y = 0;
	map->pos.exit_x = 0;
	map->pos.exit_y = 0;
}

t_img	load_image(void	*mlx, char *path)
{
	t_img	img;

	img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.img_var)
		return (img);
	img.addr = mlx_get_data_addr(img.img_var, &img.bits_per_pixel, &img.line_length, &img.endian);
	return (img);
}

void	init_collect(t_master *master)
{
	master->img = load_image(master->mlx, "Mario.XPM");
	if (!(master->img.img_var))
	{
		printf("Error in getting player image\n");
		free_all(master);
	}
}

void	init_player(t_master *master)
{
	master->img = load_image(master->mlx, "Mario.XPM");
	if (!(master->img.img_var))
	{
		printf("Error in getting player image\n");
		free_all(master);
	}
}


void	my_mlx_pixel_put(t_master *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	walk(t_master *master)
{
	master->img.img_var = mlx_new_image(master->mlx, master->win_w, master->win_h);
	master->img.addr = mlx_get_data_addr(master->img.img_var, &master->img.bits_per_pixel, &master->img.line_length, &master->img.endian);
	my_mlx_pixel_put(master, master->map.pos.player_x, master->map.pos.player_y, 0x00FF0000);
	mlx_put_image_to_window(master->mlx, master->win, master->img.img_var, 0, 0);
	return (0);
}

int	player_mov(int keycode, t_master *master)
{
	if (keycode == 0)
		master->map.pos.player_x -= 10;
	else if (keycode == 1)
		master->map.pos.player_y += 10;
	else if (keycode == 2)
		master->map.pos.player_x += 10;
	else if (keycode == 13)
		master->map.pos.player_y -= 10;
	walk(master);
	return (0);
}

void	init_master(t_master *master)
{
	master->win_h = 0;
	master->win_w = 0;
}

void	start_game(t_master master)
{

	master.win_h = 1000;
	master.win_w = 1000;
	master.map.pos.player_x = master.win_w / 2;
	master.map.pos.player_y = master.win_h / 2;
	master.mlx = mlx_init();
	master.win = mlx_new_window(master.mlx, master.win_w, master.win_h, "fds");
	master.img.img_var = mlx_new_image(master.mlx, master.win_w, master.win_h);
	master.img.addr = mlx_get_data_addr(master.img.img_var, &master.img.bits_per_pixel, &master.img.line_length, &master.img.endian);
	mlx_loop_hook(master.mlx, walk, &master);
	mlx_key_hook(master.win, player_mov, &master);
	mlx_hook(master.win, 02, 1L << 2, player_mov, &master);
	// my_mlx_pixel_put(img.img, master.player_x, master.player_y, 0xFF000000);
	// mlx_put_image_to_window(master.mlx, master.win, img.img, 0, 0);
	mlx_loop(master.mlx);
}

int main(int ac, char **av)
{
	int			fd;
	t_master	master;

	init_map(&master.map);
	init_master(&master);

	if (ac != 2)
		return (-1);
	if (!check_file(av[1], ".ber"))
		return (-1);
	fd = open(av[1], O_RDONLY);
	parse_file(fd, &master.map);
	close(fd);
	start_game(master);
}
