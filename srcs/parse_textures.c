/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/25 19:20:00 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	set_tex_no_so(t_scene *scn, const char *id, char *p)
{
	if (!ft_strncmp(id, "NO", 2))
	{
		if (scn->tex_no)
			return (-1);
		scn->tex_no = ft_strdup(p);
		return (0);
	}
	if (!ft_strncmp(id, "SO", 2))
	{
		if (scn->tex_so)
			return (-1);
		scn->tex_so = ft_strdup(p);
		return (0);
	}
	return (1);
}

static int	set_tex_we_ea(t_scene *scn, const char *id, char *p)
{
	if (!ft_strncmp(id, "WE", 2))
	{
		if (scn->tex_we)
			return (-1);
		scn->tex_we = ft_strdup(p);
		return (0);
	}
	if (!ft_strncmp(id, "EA", 2))
	{
		if (scn->tex_ea)
			return (-1);
		scn->tex_ea = ft_strdup(p);
		return (0);
	}
	return (1);
}

static int	set_tex(t_scene *scn, const char *id, char *p)
{
	int	r;

	if (!*p)
		return (-1);
	r = set_tex_no_so(scn, id, p);
	if (r != 1)
		return (r);
	return (set_tex_we_ea(scn, id, p));
}

int	parse_texline(char *ln, t_scene *scn)
{
	char	*p;

	p = ln;
	if (!ft_strncmp(p, "NO", 2) || !ft_strncmp(p, "SO", 2)
		|| !ft_strncmp(p, "WE", 2) || !ft_strncmp(p, "EA", 2))
	{
		p += 2;
		while (*p == ' ' || *p == '\t')
			p++;
		rstrip(p);
		return (set_tex(scn, ln, p));
	}
	return (1);
}
