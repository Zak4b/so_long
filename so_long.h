/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:23:00 by asene             #+#    #+#             */
/*   Updated: 2025/02/14 19:16:38 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include <mlx.h>
# include "srcs/mlx_utils.h"

# define CELL_SIZE 80
# define MOVE_DISTANCE 8

# define ERROR_ARGS "Usage: %s <FILE>\n"
# define ERROR_BER "\"%s\" is not a .ber file\n"
# define ERROR_FILE "Can't open file \"%s\"\n"
# define ERROR_PARSING "Invalid map, parsing failed\n"

typedef enum e_type
{
	PLAYER = 0,
	MONSTER = 1
}	t_type;

typedef struct s_entity
{
	int		x;
	int		y;
	float	speed;
	int		dir;
	int		mov;
	t_type	type;
	int		anim_state;
	int		last_dir;
	int		last_mov;
}	t_entity;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

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
	t_mlx		*mlx;
	t_entity	*player;
	int			move_count;
	t_map		*map;
	t_img		*buffer[2];
	t_img		**img[2][4][4];
	t_list		*entities;
	t_img		**digits;
	t_img		*floor;
	t_img		*wall;
	t_img		*item;
	t_img		**exit;
}	t_game;

typedef enum e_keycode
{
	KEY_SPACE = 32,
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

typedef enum e_state
{
	IDLE = 0,
	WALK = 1,
	ATTACK = 2,
	DEAD = 3
}	t_state;

int			key_down_hook(int keycode, t_game *game);
int			key_up_hook(int keycode, t_game *game);
int			close_window(t_game *game);
int			game_loop(t_game *game);

t_map		*init_map(void);
void		clear_map(t_map *map);
t_map		*dup_map(t_map *map);
t_point		new_point(int x, int y);

t_map		*parse_map(int fd);
int			check_map(t_map *map);

t_entity	*new_entity(t_type type, int x, int y);
int			move_entity(t_game *game, t_entity *e);
void		move_entities(t_game *game);
void		check_collide(t_game *game);
int			pickup_item(t_game *game);
char		check_coords(t_map *map, int x, int y);

int			distance(int x1, int y1, int x2, int y2);
int			distance_to_exit(t_game *game);
int			distance_entity(t_entity *e1, t_entity *e2);

void		render_cell(t_game *game, int x, int y);
void		print_map(t_game *game);
void		render_entity(t_game *game, t_entity *e);
void		render_entities(t_game *game);
void		render_move_count(t_game *game, unsigned int nb);

#endif