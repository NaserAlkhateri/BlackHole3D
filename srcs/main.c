/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:34 by amersha           #+#    #+#             */
/*   Updated: 2025/08/21 23:23:42 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int error_msg(const char *s)
{
    write(2, "Error\n", 6);
    if (s)
        write(2, s, ft_strlen(s));
    write(2, "\n", 1);
    return (1);
}

int	main(int ac, char **av)
{
	const char	*err;
	t_scene		scn;
	t_mlx		m;

	if (ac != 2)
		return (error_msg("Usage: ./cub3D maps/tutorial.cub"));
	
	err = parse_scene(av[1], &scn);
	if (err)
		return (error_msg(err));
	
	err = validate_map(&scn);
	if (err)
		return (error_msg(err));
	
	init_player_from_map(&scn);
	
	if (init_mlx(&m, &scn))
		return (error_msg("MiniLibX init failed"));
	
	err = load_textures(&m, &scn);
	if (err)
	{
		destroy_and_exit(&m, 1);
		return (error_msg(err));
	}
	
	render_frame(&m);
	set_hooks(&m);
	mlx_loop(m.mlx);
	destroy_and_exit(&m, 0);
	return (0);
}
