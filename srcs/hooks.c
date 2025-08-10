/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:34:19 by amersha           #+#    #+#             */
/*   Updated: 2025/08/10 15:14:48 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	on_key(int key, t_mlx *m)
{
	(void)m;
	if (key == KEY_ESC_L || key == KEY_ESC_M)
		destroy_and_exit(m, 0);
	return (0);
}

int	on_close(t_mlx *m)
{
	destroy_and_exit(m, 0);
	return (0);
}

void	set_hooks(t_mlx *m)
{
	mlx_key_hook(m->win, on_key, m);
	mlx_hook(m->win, 17, 0, on_close, m);
}
