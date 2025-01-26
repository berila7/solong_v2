/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:57:57 by mberila           #+#    #+#             */
/*   Updated: 2025/01/26 11:13:51 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	f(void)
{
	system("leaks so_long");
	system("lsof | grep '^so_long'");
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == ESCKEY)
	{
		free_game(game);
		exit(0);
	}
	if (keycode == KEYUP || keycode == KEYDOWN
		|| keycode == KEYLEFT || keycode == KEYRIGHT)
	{
		move_player(game, keycode);
		render_map(game);
	}
	return (0);
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

static int	setup_game(t_game *game, char *map_path)
{
	if (!read_map(game, map_path))
		return (0);
	if (!validate_map(game))
		return (0);
	if (!init_mlx(game))
		return (0);
	if (!init_game_window(game))
		return (0);
	if (!init_textures(game))
		return (0);
	if (!render_map(game))
		return (0);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, ON_DESTROY, NO_EVENT_MASK, close_window, game);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	atexit (f);
	if (ac != 2)
	{
		print_error(ERR_MAP_ARG);
		return (1);
	}
	game = init_game();
	if (!game)
		return (1);
	if (!setup_game(game, av[1]))
	{
		free_game(game);
		return (1);
	}
	mlx_loop(game->mlx);
	free_game(game);
	return (0);
}
