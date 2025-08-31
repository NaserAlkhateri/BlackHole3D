/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:05:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/23 21:49:55 by amersha          ###   ########.fr       */
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

static void	free_trims(t_textrim *t)
{
	free(t->no);
	free(t->so);
	free(t->we);
	free(t->ea);
}

static const char	*ret_err_free(const char *msg, t_textrim *t)
{
	free_trims(t);
	return (msg);
}

const char	*load_textures(t_mlx *m, t_scene *scn)
{
	t_textrim	t;

	if (!m || !scn)
		return ("Invalid arguments");
	t.no = ft_strtrim(scn->tex_no, " \t\n\r");
	t.so = ft_strtrim(scn->tex_so, " \t\n\r");
	t.we = ft_strtrim(scn->tex_we, " \t\n\r");
	t.ea = ft_strtrim(scn->tex_ea, " \t\n\r");
	if (load_one(m->mlx, &m->no, t.no))
		return (ret_err_free("Cannot open texture file: NO", &t));
	if (load_one(m->mlx, &m->so, t.so))
		return (ret_err_free("Cannot open texture file: SO", &t));
	if (load_one(m->mlx, &m->we, t.we))
		return (ret_err_free("Cannot open texture file: WE", &t));
	if (load_one(m->mlx, &m->ea, t.ea))
		return (ret_err_free("Cannot open texture file: EA", &t));
	free_trims(&t);
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
