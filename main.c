/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/02 17:07:27 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_game *game)
{
	int 	i;
	int 	j;
	void	*img;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->data[i][j] == '1')
				img = game->wall_img->img;
			else
				img = game->floor_img->img;
			mlx_put_image_to_window(game->mlx, game->mlx_win, img, j++ * CELL_SIZE, i * CELL_SIZE);
		}
		i++;
	}
}

int loop(t_game *game)
{
	static int	time = 0;
	static int	t = 0;
	t_list	*img;
	int i;

	if (time % 3000 == 0)
	{
		time = 0;
		t++;
		if (t > 5)
			t = 0;
		mlx_clear_window(game->mlx, game->mlx_win);
		i = 0;
		img = game->img[game->player.dir];
		while (i < t)
		{
			i++;
			img = img->next;
		}
		print_map(game);
		put_image(game, (t_img *)(img->content), game->player.x, game->player.y);
		mlx_do_sync(game->mlx);
	}
	time++;
	return (1);
}


void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->map->width * CELL_SIZE, game->map->height * CELL_SIZE, "Hello world!");
	game->img[D_DOWN] = load_sprites(game, "./assets/pf", 6);
	game->img[D_UP] = load_sprites(game, "./assets/pb", 6);
	game->img[D_RIGHT] = load_sprites(game, "./assets/pr", 6);
	game->img[D_LEFT] = load_sprites(game, "./assets/pl", 6);
	game->floor_img = load_img(game, "./assets/grass.xpm");
	game->wall_img = load_img(game, "./assets/wall.xpm");
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
    mlx_key_hook(game->mlx_win, key_hook, game);
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir = 3;
	mlx_loop_hook(game->mlx, loop, game);
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
	mlx_loop(game.mlx);
}
