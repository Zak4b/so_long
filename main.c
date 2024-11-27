/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/11/27 15:00:12 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_hook(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        exit(0);
	else if (keycode == KEY_W)
		game->pos_y--;
	else if (keycode == KEY_A)
		game->pos_x--;
	else if (keycode == KEY_S)
		game->pos_y++;
	else if (keycode == KEY_D)
		game->pos_x++;
	mlx_pixel_put(game->mlx, game->mlx_win, game->pos_x, game->pos_y, 0x00FF0000);
    return 0;
}
int close_window(void *param)
{
    (void)param;
    exit(0);
    return 0;
}

void	init_game(t_game *game)
{
	int	img_width;
    int	img_height;
	t_data	img;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 1920, 1080, "Hello world!");
	img.img = mlx_xpm_file_to_image(game->mlx, "./test.xpm", &img_width, &img_height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                    &img.endian);
	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
	mlx_hook(game->mlx_win, 17, 0, close_window, NULL);
    mlx_key_hook(game->mlx_win, key_hook, game);
	game->pos_x = 50;
	game->pos_y = 50;
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	if (argc != 2)
		return (ft_fprintf(2, "Usage: %s <FILE>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, "Can't open file \"%s\"\n", argv[1]), 1);
	map = parse_map(fd);
	close(fd);

	ft_printf("%d %d\n", map->height, map->width);
	ft_lstclear(&(map->map_data), free);
	free(map);
}
