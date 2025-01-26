/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:24:09 by mberila           #+#    #+#             */
/*   Updated: 2025/01/26 11:48:54 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	init_animations(t_game *game)
{
	int		i;
	char	*collect_paths[ANIMATION_FRAMES];

	collect_paths[0] = "./bonus/textures/collectable/c_1.xpm";
	collect_paths[1] = "./bonus/textures/collectable/c_2.xpm";
	collect_paths[2] = "./bonus/textures/collectable/c_3.xpm";
	collect_paths[3] = "./bonus/textures/collectable/c_4.xpm";
	collect_paths[4] = "./bonus/textures/collectable/c_5.xpm";
	i = 0;
	while (i < ANIMATION_FRAMES)
	{
		game->collect_frames[i] = load_texture(game, collect_paths[i]);
		if (!game->collect_frames[i])
		{
			ft_printf("Error\nFailed to load collectible texture %d\n", i + 1);
			free_game(game);
			exit(1);
		}
		i++;
	}
	game->collect_current_frame = 0;
	game->animation_timer = 0;
}

void	update_animations(t_game *game)
{
	game->animation_timer++;
	if (game->animation_timer >= ANIMATION_SPEED)
	{
		game->collect_current_frame
			= (game->collect_current_frame + 1) % ANIMATION_FRAMES;
		game->animation_timer = 0;
	}
}
