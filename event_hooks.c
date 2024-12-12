/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2024/12/12 15:14:23 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_down_hook(int k, t_game *game)
{
	if (k == KEY_A || k == KEY_W || k == KEY_D || k == KEY_S)
		game->player->mov = 1;
	if (k == KEY_A)
		game->player->dir = D_LEFT;
	else if (k == KEY_W)
		game->player->dir = D_UP;
	else if (k == KEY_D)
		game->player->dir = D_RIGHT;
	else if (k == KEY_S)
		game->player->dir = D_DOWN;
	else if (k == KEY_ESC)
		close_window(game);
	return (0);
}

int	key_up_hook(int k, t_game *game)
{
	if (k == KEY_A && game->player->dir == D_LEFT)
		game->player->mov = 0;
	else if (k == KEY_W && game->player->dir == D_UP)
		game->player->mov = 0;
	else if (k == KEY_D && game->player->dir == D_RIGHT)
		game->player->mov = 0;
	else if (k == KEY_S && game->player->dir == D_DOWN)
		game->player->mov = 0;
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
		clear_array_img(game, game->img[0][i]);
		clear_array_img(game, game->img[1][i]);
		clear_array_img(game, game->simg[i]);
		i++;
	}
	free(game->player);
	ft_lstclear(&game->enemies, free);
	free_image(game, game->floor);
	free_image(game, game->wall);
	free_image(game, game->item);
	free_image(game, game->exit[0]);
	free_image(game, game->exit[1]);
	clear_array_img(game, game->digits);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	game_loop(t_game *game)
{
	print_map(game);
	if (move_entity(game, game->player) && ++(game->move_count) % 10 == 0)
		ft_printf("Move : %d \n", game->move_count / 10);
	move_enemies(game);
	if (pickup_item(game) && game->map->items == 0)
		render_cell(game, game->map->exit.x, game->map->exit.y);
	if (game->map->items == 0
		&& check_coords(game->map, game->player->x, game->player->y) == 'E')
		close_window(game);
	render_entity(game, game->player);
	render_enemies(game);
	render_move_count(game, game->move_count / 10);
	mlx_do_sync(game->mlx);
	usleep(50000);
	return (1);
}
