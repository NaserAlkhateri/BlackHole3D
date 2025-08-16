/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:05:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/16 12:44:45 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	load_one(void *mlx, t_img *im, char *path)
{
	im->img = mlx_xpm_file_to_image(mlx, path, &im->w, &im->h);
	if (!im->img)
		return (1);
	im->addr = mlx_get_data_addr(im->img, &im->bpp, &im->line_len, &im->endian);
	return (0);
}

const char	*load_textures(t_mlx *m, t_scene *scn)
{
	if (!m || !scn)
		return ("Invalid arguments");
	if (load_one(m->mlx, &m->no, scn->tex_no))
		return ("Cannot open texture file: NO");
	if (load_one(m->mlx, &m->so, scn->tex_so))
		return ("Cannot open texture file: SO");
	if (load_one(m->mlx, &m->we, scn->tex_we))
		return ("Cannot open texture file: WE");
	if (load_one(m->mlx, &m->ea, scn->tex_ea))
		return ("Cannot open texture file: EA");
	return (NULL);
}

void	free_textures(t_mlx *m)
{
	if (m->no.img)
		mlx_destroy_image(m->mlx, m->no.img);
	if (m->so.img)
		mlx_destroy_image(m->mlx, m->so.img);
	if (m->we.img)
		mlx_destroy_image(m->mlx, m->we.img);
	if (m->ea.img)
		mlx_destroy_image(m->mlx, m->ea.img);
}
