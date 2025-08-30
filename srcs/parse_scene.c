/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/30 14:55:36 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ps(t_ps *ps, t_scene *scn)
{
	ps->got_f = 0;
	ps->got_c = 0;
	ps->in_map = 0;
	ps->acc = NULL;
	ps->loop_res = NULL;
	scn->tex_no = NULL;
	scn->tex_so = NULL;
	scn->tex_we = NULL;
	scn->tex_ea = NULL;
}

void	invalid_cub(t_ps *ps)
{
	free(ps->ln);
	close(ps->fd);
	free(ps->acc);
}

static int	can_open(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

char	*file_check(t_ps *ps, t_scene *scn)
{
	if (!scn->tex_no || !scn->tex_so || !scn->tex_we || !scn->tex_ea)
		return (free(ps->acc), "Missing texture identifier (NO/SO/WE/EA)");
	if (!ps->got_f)
		return (free(ps->acc), "Missing floor color (F)");
	if (!ps->got_c)
		return (free(ps->acc), "Missing ceiling color (C)");
	if (!can_open(scn->tex_no))
		return (free(ps->acc), "Cannot open texture file: NO");
	if (!can_open(scn->tex_so))
		return (free(ps->acc), "Cannot open texture file: SO");
	if (!can_open(scn->tex_we))
		return (free(ps->acc), "Cannot open texture file: WE");
	if (!can_open(scn->tex_ea))
		return (free(ps->acc), "Cannot open texture file: EA");
	if (map_finalize(scn, ps->acc))
		return ("Map parsing failed");
	return (NULL);
}

const char	*parse_scene(const char *path, t_scene *scn)
{
	t_ps		ps;
	const char	*err;
	size_t		n;

	if (!path || !scn)
		return ("Invalid arguments");
	n = ft_strlen(path);
	if (n < 4 || ft_strncmp(path + (n - 4), ".cub", 4) != 0)
		return ("only *.cub files are allowed");
	ps.fd = open(path, O_RDONLY);
	if (ps.fd < 0)
		return ("Cannot open file");
	init_ps(&ps, scn);
	ps.ln = get_next_line(ps.fd);
	while (ps.ln)
	{
		err = handle_line(&ps, scn);
		if (err)
			return (err);
		free(ps.ln);
		ps.ln = get_next_line(ps.fd);
	}
	close(ps.fd);
	return (file_check(&ps, scn));
}
