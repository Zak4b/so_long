/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2025/02/14 19:29:06 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	init_images(t_game *g)
{
	g->img[PLAYER][IDLE][D_DOWN] = load_sprites(g->mlx, "./assets/player/idle/pif", 6);
	g->img[PLAYER][IDLE][D_UP] = load_sprites(g->mlx, "./assets/player/idle/pib", 6);
	g->img[PLAYER][IDLE][D_RIGHT] = load_sprites(g->mlx, "./assets/player/idle/pir", 6);
	g->img[PLAYER][IDLE][D_LEFT] = load_sprites(g->mlx, "./assets/player/idle/pil", 6);
	g->img[PLAYER][WALK][D_DOWN] = load_sprites(g->mlx, "./assets/player/walk/pwf", 6);
	g->img[PLAYER][WALK][D_UP] = load_sprites(g->mlx, "./assets/player/walk/pwb", 6);
	g->img[PLAYER][WALK][D_RIGHT] = load_sprites(g->mlx, "./assets/player/walk/pwr", 6);
	g->img[PLAYER][WALK][D_LEFT] = load_sprites(g->mlx, "./assets/player/walk/pwl", 6);
	g->img[PLAYER][ATTACK][D_DOWN] = load_sprites(g->mlx, "./assets/player/attack/paf", 4);
	g->img[PLAYER][ATTACK][D_UP] = load_sprites(g->mlx, "./assets/player/attack/pab", 4);
	g->img[PLAYER][ATTACK][D_RIGHT] = load_sprites(g->mlx, "./assets/player/attack/par", 4);
	g->img[PLAYER][ATTACK][D_LEFT] = load_sprites(g->mlx, "./assets/player/attack/pal", 4);
	g->img[PLAYER][DEAD][0] = load_sprites(g->mlx, "./assets/player/death/pd", 3);
	g->img[MONSTER][WALK][D_DOWN] = load_sprites(g->mlx, "./assets/slime/sf", 6);
	g->img[MONSTER][WALK][D_UP] = load_sprites(g->mlx, "./assets/slime/sb", 6);
	g->img[MONSTER][WALK][D_RIGHT] = load_sprites(g->mlx, "./assets/slime/sr", 6);
	g->img[MONSTER][WALK][D_LEFT] = load_sprites(g->mlx, "./assets/slime/sl", 6);
	g->img[MONSTER][DEAD][0] = load_sprites(g->mlx, "./assets/slime/sd", 5);
	g->floor = load_img(g->mlx, "./assets/grass.xpm");
	g->wall = load_img(g->mlx, "./assets/wall.xpm");
	g->item = load_img(g->mlx, "./assets/coin.xpm");
	g->exit = load_sprites(g->mlx, "./assets/trap", 2);
	g->digits = load_sprites(g->mlx, "./assets/digits/", 10);
}

void	init_entities(t_game *game)
{
	int			x;
	int			y;
	t_entity	*e;

	game->entities = NULL;
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
				e->speed = 0.8;
				ft_lstadd_back(&game->entities, ft_lstnew(e));
			}
			x++;
		}
		y++;
	}
	ft_lstadd_back(&game->entities, ft_lstnew(game->player));
}

void	init_game(t_game *game)
{
	int	win_width;
	int	win_height;

	win_width = game->map->width * CELL_SIZE;
	win_height = game->map->height * CELL_SIZE;
	game->mlx = t_mlx_init(win_width, win_height, "So Looooooooooong!");
	init_images(game);
	game->buffer[0] = new_image(game->mlx, win_width, win_height);
	game->buffer[1] = new_image(game->mlx, win_width, win_height);
	game->player = new_entity(PLAYER, (game->map->entrance.x + 0.5) * CELL_SIZE,
			(game->map->entrance.y + 0.5) * CELL_SIZE);
	game->move_count = 0;
	init_entities(game);
	mlx_hook(game->mlx->window, 17, 0, close_window, game);
	mlx_hook(game->mlx->window, 2, 1L << 0, key_down_hook, game);
	mlx_hook(game->mlx->window, 3, 1L << 1, key_up_hook, game);
	mlx_loop_hook(game->mlx->instance, game_loop, game);
	mlx_do_key_autorepeatoff(game->mlx->instance);
	print_map(game);
}

int	open_file(char *path, int *fd)
{
	int	i;

	i = ft_strlen(path) - 4;
	if (i < 0 || ft_strncmp(path + i, ".ber", 4))
		return (ft_fprintf(2, ERROR_BER, path), 0);
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (ft_fprintf(2, ERROR_FILE, path), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	if (argc != 2)
		return (ft_fprintf(2, ERROR_ARGS, argv[0]), EXIT_FAILURE);
	if (!open_file(argv[1], &fd))
		return (EXIT_FAILURE);
	game.map = parse_map(fd);
	close(fd);
	get_next_line(fd);
	if (game.map == NULL)
		return (ft_fprintf(2, ERROR_PARSING), EXIT_FAILURE);
	else if (!check_map(game.map))
		return (clear_map(game.map), EXIT_FAILURE);
	init_game(&game);
	mlx_loop(game.mlx->instance);
}
