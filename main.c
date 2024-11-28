/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/11/28 17:20:09 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	int	img_width;
    int	img_height;
	t_data	img;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 1920, 1080, "Hello world!");
	img.img = mlx_xpm_file_to_image(game->mlx, "./assets/player.xpm", &img_width, &img_height);
	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
    mlx_key_hook(game->mlx_win, key_hook, game);
	game->player.x = 50;
	game->player.y = 50;
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;
	if (argc != 2)
		return (ft_fprintf(2, "Usage: %s <FILE>\n", argv[0]), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, "Can't open file \"%s\"\n", argv[1]), EXIT_FAILURE);
	game.map = parse_map(fd);
	close(fd);
	if (game.map == NULL)
		return (ft_fprintf(2, "Invalid map, parsing failed\n"), EXIT_FAILURE);
	init_game(&game);
}
