/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2024/12/21 23:59:33 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	free_all_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		clear_array_img(game, game->img[IDLE][i]);
		clear_array_img(game, game->img[WALK][i]);
		clear_array_img(game, game->img[ATTACK][i]);
		clear_array_img(game, game->simg[WALK][i]);
		i++;
	}
	clear_array_img(game, game->img[DEAD][0]);
	clear_array_img(game, game->simg[DEAD][0]);
	clear_array_img(game, game->digits);
	free_image(game, game->buffer[0]);
	free_image(game, game->buffer[1]);
	free_image(game, game->floor);
	free_image(game, game->wall);
	free_image(game, game->item);
	free_image(game, game->exit[0]);
	free_image(game, game->exit[1]);
}

int	close_window(t_game *game)
{
	mlx_do_key_autorepeaton(game->mlx);
	clear_map(game->map);
	free_all_images(game);
	free(game->player);
	ft_lstclear(&game->enemies, free);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	game_loop(t_game *g)
{
	clock_t	time;

	time = clock();
	ft_memcpy(g->buffer[1]->addr, g->buffer[0]->addr,
		g->buffer[0]->height * g->buffer[0]->line_length);
	move_entity(g, g->player);
	move_enemies(g);
	check_collide(g);
	if (pickup_item(g) && g->map->items == 0)
	{
		render_cell(g, g->player->x / CELL_SIZE, g->player->y / CELL_SIZE);
		render_cell(g, g->map->exit.x, g->map->exit.y);
	}
	if (g->map->items == 0 && distance_to_exit(g) <= 8)
		close_window(g);
	render_enemies(g);
	render_entity(g, g->player);
	render_move_count(g, g->move_count / 10);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->buffer[1]->img, 0, 0);
	mlx_do_sync(g->mlx);
	time = 55000 - (clock() - time) * 1000000 / CLOCKS_PER_SEC;
	if (time > 0)
		usleep(time);
	return (1);
}
