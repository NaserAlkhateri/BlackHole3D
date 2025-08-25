/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:35:28 by amersha           #+#    #+#             */
/*   Updated: 2025/08/25 19:20:00 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_split(char **sp)
{
	int	i;

	if (!sp)
		return ;
	i = 0;
	while (sp[i])
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}


static int	rgb_split_3(const char *s, char ***out_sp)
{
	char	**sp;

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
	{
		free_split(sp);
		return (1);
	}
	*out_sp = sp;
	return (0);
}

static int	rgb_values_valid(int vals[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (vals[i] < 0 || vals[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

static void	rgb_store(t_color *out, int vals[3])
{
	out->r = vals[0];
	out->g = vals[1];
	out->b = vals[2];
	out->rgb = (out->r << 16) | (out->g << 8) | out->b;
}

int	parse_rgb(const char *s, t_color *out)
{
	char	**sp;
	int		vals[3];

	if (!s || !out)
		return (1);
	if (rgb_split_3(s, &sp))
		return (1);
	vals[0] = ft_atoi(sp[0]);
	vals[1] = ft_atoi(sp[1]);
	vals[2] = ft_atoi(sp[2]);
	if (!rgb_values_valid(vals))
	{
		free_split(sp);
		return (1);
	}
	rgb_store(out, vals);
	free_split(sp);
	return (0);
}
