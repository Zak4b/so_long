/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:57:27 by asene             #+#    #+#             */
/*   Updated: 2024/12/16 11:44:56 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	line_is_valid(const char *line)
{
	int	i;

	i = 0;
	if (line[i] != '1')
		return (0);
	while (line[i] && ft_strchr("01CEPM", line[i]))
		i++;
	if (i >= 3)
		return (line[i] == '\0' && line[i - 1] == '1');
	return (0);
}

void	sanitize_line(char **line)
{
	char	*n;

	n = ft_strchr(*line, '\n');
	if (n != NULL)
		*n = '\0';
}

t_list	*map_list(int fd, int *width, int *height)
{
	t_list	*lst;
	char	*line;

	lst = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		sanitize_line(&line);
		if (*width == -1)
			*width = ft_strlen(line);
		else if ((size_t)(*width) != ft_strlen(line) || ft_strlen(line) < 3
			|| !line_is_valid(line))
			return (free(line), ft_lstclear(&lst, free), NULL);
		ft_lstadd_back(&lst, ft_lstnew(line));
		(*height)++;
	}
	return (lst);
}

t_map	*parse_map(int fd)
{
	int		i;
	t_list	*lst_start;
	t_list	*lst;
	t_map	*map;

	map = init_map();
	lst_start = map_list(fd, &(map->width), &(map->height));
	if (lst_start == NULL)
		return (free(map), NULL);
	lst = lst_start;
	i = 0;
	map->data = ft_calloc(map->height + 1, sizeof(char *));
	while (i < map->height)
	{
		map->data[i++] = lst->content;
		lst = lst->next;
	}
	ft_lstclear(&lst_start, NULL);
	i = 0;
	while (i < map->width && (map->data[0][i] == '1')
		&& (map->data[map->height - 1][i] == '1'))
		i++;
	if (i != map->width)
		return (clear_map(map), NULL);
	return (map);
}
