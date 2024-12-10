/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/10 18:05:33 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
			render_cell(game, x++, y);
		y++;
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->map->width * CELL_SIZE,
			game->map->height * CELL_SIZE, "So Looooooooooong!");
	game->img[0][D_DOWN] = load_sprites(game, "./assets/player/idle/pif", 6);
	game->img[0][D_UP] = load_sprites(game, "./assets/player/idle/pib", 6);
	game->img[0][D_RIGHT] = load_sprites(game, "./assets/player/idle/pir", 6);
	game->img[0][D_LEFT] = load_sprites(game, "./assets/player/idle/pil", 6);
	game->img[1][D_DOWN] = load_sprites(game, "./assets/player/walk/pwf", 6);
	game->img[1][D_UP] = load_sprites(game, "./assets/player/walk/pwb", 6);
	game->img[1][D_RIGHT] = load_sprites(game, "./assets/player/walk/pwr", 6);
	game->img[1][D_LEFT] = load_sprites(game, "./assets/player/walk/pwl", 6);
	game->floor = load_img(game, "./assets/grass.xpm");
	game->wall = load_img(game, "./assets/wall.xpm");
	game->item = load_img(game, "./assets/coin.xpm");
	game->exit[0] = load_img(game, "./assets/trap0.xpm");
	game->exit[1] = load_img(game, "./assets/trap1.xpm");
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_down_hook, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_up_hook, game);
	game->player.x = (game->map->entrance.x + 0.5) * CELL_SIZE;
	game->player.y = (game->map->entrance.y + 0.5) * CELL_SIZE;
	game->player.mov = 0;
	game->player.dir = D_RIGHT;
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_do_key_autorepeatoff(game->mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	if (argc != 2)
		return (ft_fprintf(2, "Usage: %s <FILE>\n", argv[0]), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, "Can't open file \"%s\"\n", argv[1]), 1);
	game.map = parse_map(fd);
	close(fd);
	if (game.map == NULL)
		return (ft_fprintf(2, "Invalid map, parsing failed\n"), EXIT_FAILURE);
	else if (!check_map(game.map))
		return (clear_map(game.map),
			ft_fprintf(2, "Invalid map, can't reach all items and exit\n"), 1);
	init_game(&game);
	mlx_loop(game.mlx);
}
