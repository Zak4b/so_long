/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:23:00 by asene             #+#    #+#             */
/*   Updated: 2024/12/11 15:20:08 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"

# define CELL_SIZE 80
# define MOVE_DISTANCE 8

typedef struct s_img
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	int	x;
	int	y;
	int	dir;
	int	mov;
}	t_player;

typedef struct s_point
{
	int	x;
	int	y;
} t_point;

typedef struct s_map
{
	int		width;
	int		height;
	char	**data;
	int		items;
	t_point	entrance;
	t_point	exit;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	int			move_count;
	t_map		*map;
	t_list		*img[2][4];
	t_img		**digits;
	t_img		*floor;
	t_img		*wall;
	t_img		*item;
	t_img		*exit[2];
}	t_game;

typedef enum e_keycode
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100
}	t_keycode;

typedef enum e_direction
{
	D_LEFT = 0,
	D_UP = 1,
	D_RIGHT = 2,
	D_DOWN = 3
}	t_direction;

t_img	*load_img(t_game *game, char *path);
t_list	*load_sprites(t_game *game, char *path, unsigned int count);
t_img	**load_sprites_array(t_game *game, char *path, unsigned int count);
char	*build_path(char const *s1, char const *s2, int j);
void	put_image(t_game *game, t_img *img, int x_offset, int y_offset);
void	free_image(t_game *game, t_img *img);
void	clear_lst_img(t_game *game, t_list **lst);
void	clear_array_img(t_game *game, t_img **imgs);

int		key_down_hook(int keycode, t_game *game);
int		key_up_hook(int keycode, t_game *game);
int		close_window(t_game *game);
int		game_loop(t_game *game);

t_map	*init_map(void);
void	clear_map(t_map *map);
t_map	*dup_map(t_map *map);
t_point	new_point(int x, int y);

t_map	*parse_map(int fd);
int		check_map(t_map *map);

int		move_player(t_game *game);
int		pickup_item(t_game *game);
char	check_coords(t_map *map, int x, int y);

void	render_cell(t_game *game, int x, int y);
void	render_arround(t_game *game, int x0, int y0);
void	print_map(t_game *game);
void	render_player(t_game *game, int *t);
void	render_move_count(t_game *game, unsigned int nb);

#endif