/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:06:39 by mberila           #+#    #+#             */
/*   Updated: 2025/01/26 10:54:33 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static int	count_lines(char *filename)
{
	char	*line;
	int		fd;
	int		lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		return (print_error(ERR_MAP_OPEN), -1);
	}
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (lines == 0)
	{
		print_error(ERR_MAP_EMPTY);
		close(fd);
		return (-1);
	}
	close(fd);
	return (lines);
}

static int	init_map(t_game *game, char *filename)
{
	if (!check_extension(filename))
		return (0);
	game->height = count_lines(filename);
	if (game->height <= 0)
		return (0);
	game->map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!game->map)
		return (0);
	return (1);
}

static int	check_line_length(t_game *game, char *line, int line_num)
{
	int	len;

	if (ft_strchr(line, '\n'))
		len = ft_strlen(line) - 1;
	else
		len = ft_strlen(line);
	if (line_num == 0)
	{
		game->width = len;
		return (1);
	}
	if (len != game->width)
	{
		print_error(ERR_RECT);
		return (0);
	}
	return (1);
}

static int	read_lines(t_game *game, int fd)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
		{
			free_map(game->map, i);
			return (0);
		}
		if (!check_line_length(game, game->map[i], i))
		{
			free_map(game->map, i + 1);
			return (0);
		}
		i++;
	}
	game->map[i] = NULL;
	return (1);
}

int	read_map(t_game *game, char *filename)
{
	int	fd;

	if (!init_map(game, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map);
		return (0);
	}
	if (!read_lines(game, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
