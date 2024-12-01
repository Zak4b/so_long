/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/11/29 17:21:20 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void put_image_with_transparency(void *mlx, void *win, void *img, int x_offset, int y_offset)
{
    int x, y;
    int *img_data;
    int bpp, size_line, endian;
    int color;

    img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

	y = 0;
    while (y < 64)
    {
		x = 0;
        while (x < 64)
        {
            color = img_data[y * (size_line / 4) + x];
            if ((color >> 24 & 0xFF) == 0)
                mlx_pixel_put(mlx, win, x + x_offset, y + y_offset, color);
			x++;
        }
		y++;
    }
}
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
				img = game->wall_img;
			else
				img = game->floor_img;
			mlx_put_image_to_window(game->mlx, game->mlx_win, img, j++ * CELL_SIZE, i * CELL_SIZE);
		}
		i++;
	}
}

int loop(t_game *game)
{
	static unsigned int time = 0;
	t_list	*img;
	int i;

	if (time % 5000 == 0)
	{
		time = 0;
		mlx_clear_window(game->mlx, game->mlx_win);
		i = 0;
		img = game->img;
		while (i < game->player.dir)
		{
			i++;
			img = img->next;
		}
		print_map(game);
		put_image_with_transparency(game->mlx, game->mlx_win, img->content, game->player.x, game->player.y);
		mlx_do_sync(game->mlx);
	}
	time++;
	return (1);
}


void	init_game(t_game *game)
{
	int		iw;
    int		ih;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->map->width * CELL_SIZE, game->map->height * CELL_SIZE, "Hello world!");
	game->img = NULL;
	ft_lstadd_back(&(game->img), ft_lstnew(mlx_xpm_file_to_image(game->mlx, "./assets/pl.xpm", &iw, &ih)));
	ft_lstadd_back(&(game->img), ft_lstnew(mlx_xpm_file_to_image(game->mlx, "./assets/pb.xpm", &iw, &ih)));
	ft_lstadd_back(&(game->img), ft_lstnew(mlx_xpm_file_to_image(game->mlx, "./assets/pr.xpm", &iw, &ih)));
	ft_lstadd_back(&(game->img), ft_lstnew(mlx_xpm_file_to_image(game->mlx, "./assets/pf.xpm", &iw, &ih)));
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "./assets/grass.xpm", &iw, &ih);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "./assets/wall.xpm", &iw, &ih);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
    mlx_key_hook(game->mlx_win, key_hook, game);
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir = 3;
	mlx_loop_hook(game->mlx, loop, game);
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
