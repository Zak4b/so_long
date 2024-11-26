/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/11/26 17:09:20 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

	if (argc != 2)
		return (ft_fprintf(2, "Usage: %s <FILE>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, "Can't open file \"%s\"\n", argv[1]), 1);
	map = parse_map(fd);
	close(fd);

	ft_printf("%d %d\n", map->height, map->width);

	mlx_init();
	
	ft_lstclear(&(map->map_data), free);
	free(map);
}
