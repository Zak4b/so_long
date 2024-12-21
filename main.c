/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/21 22:45:12 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_images(t_game *g)
{
	g->img[IDLE][D_DOWN] = load_sprites(g, "./assets/player/idle/pif", 6);
	g->img[IDLE][D_UP] = load_sprites(g, "./assets/player/idle/pib", 6);
	g->img[IDLE][D_RIGHT] = load_sprites(g, "./assets/player/idle/pir", 6);
	g->img[IDLE][D_LEFT] = load_sprites(g, "./assets/player/idle/pil", 6);
	g->img[WALK][D_DOWN] = load_sprites(g, "./assets/player/walk/pwf", 6);
	g->img[WALK][D_UP] = load_sprites(g, "./assets/player/walk/pwb", 6);
	g->img[WALK][D_RIGHT] = load_sprites(g, "./assets/player/walk/pwr", 6);
	g->img[WALK][D_LEFT] = load_sprites(g, "./assets/player/walk/pwl", 6);
	g->img[ATTACK][D_DOWN] = load_sprites(g, "./assets/player/attack/paf", 4);
	g->img[ATTACK][D_UP] = load_sprites(g, "./assets/player/attack/pab", 4);
	g->img[ATTACK][D_RIGHT] = load_sprites(g, "./assets/player/attack/par", 4);
	g->img[ATTACK][D_LEFT] = load_sprites(g, "./assets/player/attack/pal", 4);
	g->img[DEAD][0] = load_sprites(g, "./assets/player/death/pd", 3);
	g->simg[WALK][D_DOWN] = load_sprites(g, "./assets/slime/sf", 6);
	g->simg[WALK][D_UP] = load_sprites(g, "./assets/slime/sb", 6);
	g->simg[WALK][D_RIGHT] = load_sprites(g, "./assets/slime/sr", 6);
	g->simg[WALK][D_LEFT] = load_sprites(g, "./assets/slime/sl", 6);
	g->simg[DEAD][0] = load_sprites(g, "./assets/slime/sd", 5);
	g->floor = load_img(g, "./assets/grass.xpm");
	g->wall = load_img(g, "./assets/wall.xpm");
	g->item = load_img(g, "./assets/coin.xpm");
	g->exit[0] = load_img(g, "./assets/trap0.xpm");
	g->exit[1] = load_img(g, "./assets/trap1.xpm");
	g->digits = load_sprites(g, "./assets/digits/", 10);
}

void	init_enemies(t_game *game)
{
	int			x;
	int			y;
	t_entity	*e;

	game->enemies = NULL;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->data[y][x])
		{
			if (game->map->data[y][x] == 'M')
			{
				e = new_entity(MONSTER, (x + 0.5) * CELL_SIZE,
						(y + 0.5) * CELL_SIZE);
				e->mov = WALK;
				ft_lstadd_back(&(game->enemies), ft_lstnew(e));
			}
			x++;
		}
		y++;
	}
}

void	init_buffer(t_game *game, int width, int height)
{
	game->buffer[0] = new_image(game->mlx, width, height);
	game->buffer[1] = new_image(game->mlx, width, height);
	print_map(game);
}

void	init_game(t_game *game)
{
	int	win_width;
	int	win_height;

	win_width = game->map->width * CELL_SIZE;
	win_height = game->map->height * CELL_SIZE;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, win_width,
			win_height, "So Looooooooooong!");
	init_images(game);
	init_buffer(game, win_width, win_height);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_down_hook, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_up_hook, game);
	game->player = new_entity(PLAYER, (game->map->entrance.x + 0.5) * CELL_SIZE,
			(game->map->entrance.y + 0.5) * CELL_SIZE);
	game->move_count = 0;
	init_enemies(game);
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
	get_next_line(fd);
	if (game.map == NULL)
		return (ft_fprintf(2, "Invalid map, parsing failed\n"), EXIT_FAILURE);
	else if (!check_map(game.map))
		return (clear_map(game.map),
			ft_fprintf(2, "Invalid map, can't reach all items and exit\n"), 1);
	init_game(&game);
	mlx_loop(game.mlx);
}
