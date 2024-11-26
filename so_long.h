/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:23:00 by asene             #+#    #+#             */
/*   Updated: 2024/11/26 14:16:13 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

typedef struct s_map
{
	int		width;
	int		height;
	t_list	*map_data;
}	t_map;

t_map	*parse_map(int fd);