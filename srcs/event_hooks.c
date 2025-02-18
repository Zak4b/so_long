/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2025/02/14 19:32:57 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	key_down_hook(int k, t_game *game)
{
	if (k == KEY_ESC)
		close_window(game);
	else if (game->player->mov == DEAD)
		return (0);
	else if (k == KEY_SPACE)
		game->player->mov = ATTACK;
	else if (game->player->mov == IDLE || game->player->mov == WALK)
	{
		if (k == KEY_A || k == KEY_W || k == KEY_D || k == KEY_S)
			game->player->mov = WALK;
		if (k == KEY_A)
			game->player->dir = D_LEFT;
		else if (k == KEY_W)
			game->player->dir = D_UP;
		else if (k == KEY_D)
			game->player->dir = D_RIGHT;
		else if (k == KEY_S)
			game->player->dir = D_DOWN;
	}
	return (0);
}

int	key_up_hook(int k, t_game *game)
{
	if (game->player->mov == WALK)
	{
		if ((k == KEY_A && game->player->dir == D_LEFT)
			|| (k == KEY_W && game->player->dir == D_UP)
			|| (k == KEY_D && game->player->dir == D_RIGHT)
			|| (k == KEY_S && game->player->dir == D_DOWN))
			game->player->mov = IDLE;
	}
	return (0);
}

int	close_window(t_game *game)
{
	mlx_do_key_autorepeaton(game->mlx->instance);
	clear_map(game->map);
	ft_lstclear(&game->entities, free);
	t_mlx_kill(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	game_loop(t_game *g)
{
	clock_t	time;

	time = clock();
	ft_memcpy(g->buffer[1]->addr, g->buffer[0]->addr,
		g->buffer[0]->height * g->buffer[0]->line_length);
	move_entities(g);
	if (pickup_item(g))
	{
		render_cell(g, g->player->x / CELL_SIZE, g->player->y / CELL_SIZE);
		if (g->map->items == 0)
			render_cell(g, g->map->exit.x, g->map->exit.y);
	}
	if (g->map->items == 0 && distance_to_exit(g) <= 8)
		close_window(g);
	render_entities(g);
	render_move_count(g, g->move_count / 10);
	mlx_put_image_to_window(g->mlx->instance, g->mlx->window, g->buffer[1]->img, 0, 0);
	mlx_do_sync(g->mlx->instance);
	time = 55000 - (clock() - time) * 1000000 / CLOCKS_PER_SEC;
	if (time > 0)
		usleep(time);
	return (1);
}
