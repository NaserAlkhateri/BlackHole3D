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

void	rstrip(char *s)
{
	int	len;

	if (!s)
		return ;
	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'
			|| s[len - 1] == '\t' || s[len - 1] == ' ' || s[len - 1] == '\f'
			|| s[len - 1] == '\v'))
	{
		s[len - 1] = '\0';
		len--;
	}
}

static const char	*handle_tex_phase(t_ps *ps, t_scene *scn, int *handled)
{
	ps->r = parse_texline(ps->ln, scn);
	if (ps->r == 0)
	{
		*handled = 1;
		return (NULL);
	}
	if (ps->r == -1)
	{
		invalid_cub(ps);
		return ("Duplicate/invalid texture identifier");
	}
	*handled = 0;
	return (NULL);
}

static const char	*handle_color_phase(t_ps *ps, t_scene *scn, int *handled)
{
	*handled = 1;
	if (!ps->in_map && !ps->got_f && !ft_strncmp(ps->ln, "F ", 2))
	{
		if (parse_rgb(ps->ln + 2, &scn->floor_c))
			return (invalid_cub(ps), "Invalid floor color");
		ps->got_f = 1;
		return (NULL);
	}
	if (!ps->in_map && !ps->got_c && !ft_strncmp(ps->ln, "C ", 2))
	{
		if (parse_rgb(ps->ln + 2, &scn->ceil_c))
			return (invalid_cub(ps), "Invalid ceiling color");
		ps->got_c = 1;
		return (NULL);
	}
	if (!ps->in_map && ps->got_c && !ft_strncmp(ps->ln, "C ", 2))
		return (invalid_cub(ps), "Ceiling is duplicated!");
	if (!ps->in_map && ps->got_f && !ft_strncmp(ps->ln, "F ", 2))
		return (invalid_cub(ps), "Floor is duplicated!");
	*handled = 0;
	return (NULL);
}

static const char	*handle_map_phase(t_ps *ps)
{
	ps->map_acc_result = map_accumulate(&(ps->acc), ps->ln, &(ps->in_map));
	if (ps->map_acc_result == 1)
		return (invalid_cub(ps), "Invalid content in map");
	return (NULL);
}

const char	*handle_line(t_ps *ps, t_scene *scn)
{
	const char	*err;
	int			handled;
	char		*p;
	char		*q;
	int			w;
	int			h;

	err = handle_tex_phase(ps, scn, &handled);
	if (err || handled)
		return (err);
	err = handle_color_phase(ps, scn, &handled);
	if (err || handled)
		return (err);
	p = ps->ln;
	while (*p == ' ' || *p == '\t')
		p++;
	if (!ps->in_map && *p == 'R' && (p[1] == ' ' || p[1] == '\t'))
	{
		p += 2;
		while (*p == ' ' || *p == '\t') p++;
		if (!ft_isdigit(*p)) return (invalid_cub(ps), "Invalid resolution");
		w = ft_atoi(p);
		while (ft_isdigit(*p)) p++;
		while (*p == ' ' || *p == '\t') p++;
		if (!ft_isdigit(*p)) return (invalid_cub(ps), "Invalid resolution");
		h = ft_atoi(p);
		while (ft_isdigit(*p)) p++;
		while (*p == ' ' || *p == '\t') p++;
		if (*p || w <= 0 || h <= 0) return (invalid_cub(ps), "Invalid resolution");
		return (NULL);
	}
	if (!ps->in_map)
	{
		q = p;
		while ((*q >= 'A' && *q <= 'Z')) q++;
		if (q > p && (*q == ' ' || *q == '\t'))
		{
			if (!ft_strncmp(p, "NO", 2) || !ft_strncmp(p, "SO", 2)
				|| !ft_strncmp(p, "WE", 2) || !ft_strncmp(p, "EA", 2)
				|| !ft_strncmp(p, "S", 1) || !ft_strncmp(p, "F", 1)
				|| !ft_strncmp(p, "C", 1))
				return (NULL);
			return (invalid_cub(ps), "Unknown identifier");
		}
	}
	return (handle_map_phase(ps));
}
