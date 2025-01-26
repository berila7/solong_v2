/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:49:33 by mberila           #+#    #+#             */
/*   Updated: 2025/01/26 12:36:26 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	update_player_position(t_game *game, int new_y, int new_x)
{
	int	old_x;
	int	old_y;

	find_char_pos(game, &old_x, &old_y, PLAYER);
	if (game->map[old_y][old_x] == PLAYER
		&& old_y == game->exit_pos_y
		&& old_x == game->exit_pos_x)
		game->map[old_y][old_x] = EXIT;
	else
		game->map[old_y][old_x] = EMPTY;
	game->map[new_y][new_x] = PLAYER;
}

static void	update_player_direction(t_game *game, int keycode)
{
	if (keycode == KEYUP)
		game->player_direction = P_UP;
	else if (keycode == KEYDOWN)
		game->player_direction = P_DOWN;
	else if (keycode == KEYLEFT)
		game->player_direction = P_LEFT;
	else if (keycode == KEYRIGHT)
		game->player_direction = P_RIGHT;
	game->player_img = game->player_frames[game->player_direction];
}

static void	get_new_position(int keycode, t_game *game)
{
	if (keycode == KEYUP)
		game->player_y--;
	else if (keycode == KEYDOWN)
		game->player_y++;
	else if (keycode == KEYLEFT)
		game->player_x--;
	else if (keycode == KEYRIGHT)
		game->player_x++;
}

static int	is_valid_move(t_game *game, int y, int x)
{
	if (game->map[y][x] == WALL)
		return (0);
	if (game->map[y][x] == ENEMY)
	{
		print_error(ENE_CAUGHT);
		close_window(game);
	}
	if (game->map[y][x] == EXIT && game->collect != 0)
	{
		game->exit_pos_x = x;
		game->exit_pos_y = y;
		return (1);
	}
	if (game->map[y][x] == COLLECT)
		game->collect--;
	if (game->map[y][x] == EXIT && game->collect == 0)
	{
		ft_printf("\nYou won");
		close_window(game);
	}
	return (1);
}

void	move_player(t_game *game, int keycode)
{
	find_char_pos(game, &game->player_x, &game->player_y, PLAYER);
	get_new_position(keycode, game);
	update_player_direction(game, keycode);
	if (is_valid_move(game, game->player_y, game->player_x))
	{
		update_player_position(game, game->player_y, game->player_x);
		game->moves++;
	}
}
