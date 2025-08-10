/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:34 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 15:14:54 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* tiny helper to write an error + newline */
static int	error_msg(const char *s)
{
	if (s)
		write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (1);
}

int	main(int ac, char **av)
{
	t_scene	scn;
	t_mlx	m;

	if (ac != 2)
		return (error_msg("Error\nUsage: ./cub3D maps/tutorial.cub"));
	if (parse_scene(av[1], &scn))
		return (error_msg("Error\nInvalid .cub (need F and C lines)"));
	if (init_mlx(&m, &scn))
		return (error_msg("Error\nMiniLibX init failed"));
	render_frame(&m);
	set_hooks(&m);
	mlx_loop(m.mlx);
	destroy_and_exit(&m, 0);
	return (0);
}
