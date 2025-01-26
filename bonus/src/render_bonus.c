/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:12:51 by mberila           #+#    #+#             */
/*   Updated: 2025/01/26 12:01:59 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static char	*display_moves(int n)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(n);
	if (!str)
		return (NULL);
	tmp = ft_strjoin("Moves: ", str);
	free(str);
	return (tmp);
}

static void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	put_image(game, game->floor, x, y);
	if (tile == WALL)
		put_image(game, game->wall, x, y);
	else if (tile == PLAYER)
		put_image(game, game->player_img, x, y);
	else if (tile == COLLECT)
		put_image(game,
			game->collect_frames[game->collect_current_frame], x, y);
	else if (tile == EXIT)
		put_image(game, game->exit_img, x, y);
	else if (tile == ENEMY)
		put_image(game, game->enemy_img, x, y);
}

static void	render_moves(t_game *game)
{
	char	*moves_str;

	moves_str = display_moves(game->moves);
	if (moves_str)
	{
		mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
		free (moves_str);
	}
}

int	render_map(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
	render_moves(game);
	return (1);
}
