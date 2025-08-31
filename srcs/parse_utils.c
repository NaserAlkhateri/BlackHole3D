/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/25 19:20:00 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static const char	*parse_resolution(t_ps *ps, char *p)
{
	int	w;
	int	h;

	p = skip_ws(p);
	if (!ft_isdigit(*p))
		return (invalid_cub(ps), "Invalid resolution");
	w = ft_atoi(p);
	while (ft_isdigit(*p))
		p++;
	p = skip_ws(p);
	if (!ft_isdigit(*p))
		return (invalid_cub(ps), "Invalid resolution");
	h = ft_atoi(p);
	while (ft_isdigit(*p))
		p++;
	p = skip_ws(p);
	if (*p || w <= 0 || h <= 0)
		return (invalid_cub(ps), "Invalid resolution");
	return (NULL);
}

static int	is_known_id(const char *p, size_t len)
{
	if (len == 1 && (!ft_strncmp(p, "S", 1) || !ft_strncmp(p, "F", 1)
			|| !ft_strncmp(p, "C", 1)))
		return (1);
	if (len == 2 && (!ft_strncmp(p, "NO", 2) || !ft_strncmp(p, "SO", 2)
			|| !ft_strncmp(p, "WE", 2) || !ft_strncmp(p, "EA", 2)))
		return (1);
	return (0);
}

static const char
	*check_unknown_identifier(t_ps *ps, char *p)
{
	char	*q;

	q = p;
	while (*q >= 'A' && *q <= 'Z')
		q++;
	if (q > p && (*q == ' ' || *q == '\t'))
	{
		if (is_known_id(p, (size_t)(q - p)))
			return (NULL);
		return (invalid_cub(ps), "Unknown identifier");
	}
	return (NULL);
}

const char	*handle_line(t_ps *ps, t_scene *scn)
{
	const char	*err;
	int			handled;
	char		*p;

	err = handle_tex_phase(ps, scn, &handled);
	if (err || handled)
		return (err);
	err = handle_color_phase(ps, scn, &handled);
	if (err || handled)
		return (err);
	p = skip_ws(ps->ln);
	if (!ps->in_map && *p == 'R' && (p[1] == ' ' || p[1] == '\t'))
		return (parse_resolution(ps, p + 2));
	if (!ps->in_map)
	{
		err = check_unknown_identifier(ps, p);
		if (err)
			return (err);
	}
	return (handle_map_phase(ps));
}
