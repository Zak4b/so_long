/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:31:59 by asene             #+#    #+#             */
/*   Updated: 2024/12/04 12:04:56 by asene            ###   ########.fr       */
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

	i = 0;
	while (i < game->map->height)
		free(game->map->data[i++]);
	free(game->map->data);
	free(game->map);
	i = 0;
	while (i < 4)
	{
		clear_lst_img(game, &(game->img[0][i]));
		clear_lst_img(game, &(game->img[1][i]));
		i++;
	}
	mlx_destroy_image(game->mlx, game->floor_img->img);
	free(game->floor_img);
	mlx_destroy_image(game->mlx, game->wall_img->img);
	free(game->wall_img);
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
	t_list		*img;
	int			i;

	if (time % 3000 == 0)
	{
		time = 0;
		t++;
		if (t > 5)
			t = 0;
		i = 0;
		img = game->img[game->player.mov][game->player.dir];
		while (i++ < t)
			img = img->next;
		print_map(game);
		move_player(game);
		put_image(game, img->content, game->player.x - 32, game->player.y - 32);
		mlx_do_sync(game->mlx);
	}
	time++;
	return (1);
}
