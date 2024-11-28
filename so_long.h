/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:23:00 by asene             #+#    #+#             */
/*   Updated: 2024/11/28 16:18:33 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"

# define CELL_SIZE 80

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_map
{
	int		width;
	int		height;
	char	**data;
}	t_map;

typedef struct s_game {
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_map		*map;
}	t_game;

// EVENTS
typedef enum e_keycode {
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100
} t_keycode;
int key_hook(int keycode, t_game *game);
int close_window(t_game *game);


t_map	*parse_map(int fd);

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;
#endif