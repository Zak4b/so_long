/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:23:00 by asene             #+#    #+#             */
/*   Updated: 2024/11/27 14:48:36 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include "minilibx-linux/mlx.h"

typedef struct s_map
{
	int		width;
	int		height;
	t_list	*map_data;
}	t_map;

t_map	*parse_map(int fd);

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef enum e_keycode {
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100
} t_keycode;

typedef struct s_game {
	void	*mlx;
	void	*mlx_win;
	int		pos_x;
	int		pos_y;
}	t_game;