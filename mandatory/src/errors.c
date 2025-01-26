/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:04:45 by mberila           #+#    #+#             */
/*   Updated: 2025/01/26 11:24:30 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	print_error(char *message)
{
	ft_printf("%s%s%s", RED, message, RESET);
}

int	check_extension(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strncmp(dot, ".ber", 4) != 0)
	{
		print_error(ERR_MAP_EX);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (game->height > 26 || game->width > 51)
	{
		print_error(ERR_SCREEN);
		return (0);
	}
	if (!check_walls(game))
	{
		print_error(ERR_WALLS);
		return (0);
	}
	if (!check_map_chars(game))
		return (0);
	if (!check_path(game))
		return (0);
	return (1);
}
