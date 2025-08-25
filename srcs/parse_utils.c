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

	err = handle_tex_phase(ps, scn, &handled);
	if (err)
		return (err);
	if (handled)
		return (NULL);
	err = handle_color_phase(ps, scn, &handled);
	if (err)
		return (err);
	if (handled)
		return (NULL);
	return (handle_map_phase(ps));
}
