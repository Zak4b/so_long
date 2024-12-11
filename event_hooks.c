/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2024/12/11 14:00:05 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_down_hook(int k, t_game *game)
{
	if (k == KEY_A || k == KEY_W || k == KEY_D || k == KEY_S)
		game->player.mov = 1;
	if (k == KEY_A)
		game->player.dir = D_LEFT;
	else if (k == KEY_W)
		game->player.dir = D_UP;
	else if (k == KEY_D)
		game->player.dir = D_RIGHT;
	else if (k == KEY_S)
		game->player.dir = D_DOWN;
	else if (k == KEY_ESC)
		close_window(game);
	return (0);
}

int	key_up_hook(int k, t_game *game)
{
	if (k == KEY_A && game->player.dir == D_LEFT)
		game->player.mov = 0;
	else if (k == KEY_W && game->player.dir == D_UP)
		game->player.mov = 0;
	else if (k == KEY_D && game->player.dir == D_RIGHT)
		game->player.mov = 0;
	else if (k == KEY_S && game->player.dir == D_DOWN)
		game->player.mov = 0;
	return (0);
}

int	close_window(t_game *game)
{
	int	i;

	mlx_do_key_autorepeaton(game->mlx);
	clear_map(game->map);
	i = 0;
	while (i < 4)
	{
		clear_lst_img(game, &(game->img[0][i]));
		clear_lst_img(game, &(game->img[1][i]));
		i++;
	}
	free_image(game, game->floor);
	free_image(game, game->wall);
	free_image(game, game->item);
	free_image(game, game->exit[0]);
	free_image(game, game->exit[1]);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	game_loop(t_game *game)
{
	static int	time = 0;
	static int	t = 0;

	if (time % 3000 == 0)
	{
		time = 0;
		render_arround(game, game->player.x / CELL_SIZE,
			game->player.y / CELL_SIZE);
		move_player(game);
		if (pickup_item(game) && game->map->items == 0)
			render_cell(game, game->map->exit.x, game->map->exit.y);
		if (check_coords(game->map, game->player.x, game->player.y) == 'E')
			close_window(game);
		render_player(game, &t);
		mlx_do_sync(game->mlx);
	}
	time++;
	return (1);
}
