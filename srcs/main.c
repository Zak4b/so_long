/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/31 00:49:12 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	init_images(t_game *g)
{
	static t_img	**(*l)(t_game *, char *, unsigned int) = load_sprites;

	g->img[PLAYER][IDLE][D_DOWN] = l(g, "./assets/player/idle/pif", 6);
	g->img[PLAYER][IDLE][D_UP] = l(g, "./assets/player/idle/pib", 6);
	g->img[PLAYER][IDLE][D_RIGHT] = l(g, "./assets/player/idle/pir", 6);
	g->img[PLAYER][IDLE][D_LEFT] = l(g, "./assets/player/idle/pil", 6);
	g->img[PLAYER][WALK][D_DOWN] = l(g, "./assets/player/walk/pwf", 6);
	g->img[PLAYER][WALK][D_UP] = l(g, "./assets/player/walk/pwb", 6);
	g->img[PLAYER][WALK][D_RIGHT] = l(g, "./assets/player/walk/pwr", 6);
	g->img[PLAYER][WALK][D_LEFT] = l(g, "./assets/player/walk/pwl", 6);
	g->img[PLAYER][ATTACK][D_DOWN] = l(g, "./assets/player/attack/paf", 4);
	g->img[PLAYER][ATTACK][D_UP] = l(g, "./assets/player/attack/pab", 4);
	g->img[PLAYER][ATTACK][D_RIGHT] = l(g, "./assets/player/attack/par", 4);
	g->img[PLAYER][ATTACK][D_LEFT] = l(g, "./assets/player/attack/pal", 4);
	g->img[PLAYER][DEAD][0] = l(g, "./assets/player/death/pd", 3);
	g->img[MONSTER][WALK][D_DOWN] = l(g, "./assets/slime/sf", 6);
	g->img[MONSTER][WALK][D_UP] = l(g, "./assets/slime/sb", 6);
	g->img[MONSTER][WALK][D_RIGHT] = l(g, "./assets/slime/sr", 6);
	g->img[MONSTER][WALK][D_LEFT] = l(g, "./assets/slime/sl", 6);
	g->img[MONSTER][DEAD][0] = l(g, "./assets/slime/sd", 5);
	g->floor = load_img(g, "./assets/grass.xpm");
	g->wall = load_img(g, "./assets/wall.xpm");
	g->item = load_img(g, "./assets/coin.xpm");
	g->exit = l(g, "./assets/trap", 2);
	g->digits = load_sprites(g, "./assets/digits/", 10);
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
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, win_width,
			win_height, "So Looooooooooong!");
	init_images(game);
	game->buffer[0] = new_image(game->mlx, win_width, win_height);
	game->buffer[1] = new_image(game->mlx, win_width, win_height);
	game->player = new_entity(PLAYER, (game->map->entrance.x + 0.5) * CELL_SIZE,
			(game->map->entrance.y + 0.5) * CELL_SIZE);
	game->move_count = 0;
	init_entities(game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_down_hook, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_up_hook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_do_key_autorepeatoff(game->mlx);
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
	mlx_loop(game.mlx);
}
