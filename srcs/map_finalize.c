/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_finalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:10:00 by amersha           #+#    #+#             */
/*   Updated: 2025/08/30 14:16:31 by amersha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "libft.h"
#include <stdlib.h>

static void	rows_free(char **rows)
{
	int	i;

	if (!rows)
		return ;
	i = 0;
	while (rows[i])
	{
		free(rows[i]);
		i++;
	}
	free(rows);
}

static void	get_dims(char **rows, int *h, int *w)
{
	int	i;
	int	len;

	i = 0;
	*w = 0;
	while (rows[i])
	{
		len = (int)ft_strlen(rows[i]);
		if (len > *w)
			*w = len;
		i++;
	}
	*h = i;
}

static void	pad_and_copy(char **dst, char **src, int h, int w)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	while (i < h)
	{
		len = (int)ft_strlen(src[i]);
		dst[i] = (char *)ft_calloc(w + 1, 1);
		j = 0;
		while (j < w)
		{
			if (j < len)
				dst[i][j] = src[i][j];
			else
				dst[i][j] = ' ';
			j++;
		}
		dst[i][w] = '\0';
		i++;
	}
}

int	map_finalize(t_scene *scn, char *acc)
{
	char	**rows;
	int		h;
	int		w;

	if (!acc)
		return (1);
	rows = ft_split(acc, '\n');
	free(acc);
	if (!rows)
		return (1);
	get_dims(rows, &h, &w);
	scn->map_h = h;
	scn->map_w = w;
	scn->map = (char **)ft_calloc(h + 1, sizeof(char *));
	if (!scn->map)
		return (1);
	pad_and_copy(scn->map, rows, h, w);
	rows_free(rows);
	return (0);
}
