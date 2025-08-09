/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:27:16 by nalkhate          #+#    #+#             */
/*   Updated: 2023/11/18 12:07:53 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countdest(size_t *i, size_t *size_i,
char *dst, size_t size)
{
	size_t	j;

	*i = 0;
	while (dst[*i] != '\0' && *size_i > 0)
	{
		*size_i = *size_i - 1;
		*i = *i + 1;
	}
	j = &dst[*i] - &dst[0];
	*size_i = size - j;
	return (j);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		count_dst;
	size_t		size_c;

	size_c = dstsize;
	i = 0;
	count_dst = 0;
	if ((!dst || !src) && dstsize < 1)
		return (0);
	j = countdest(&count_dst, &size_c, &dst[0], dstsize);
	if (size_c == 0)
		return (ft_strlen(src) + j);
	while (src[i] != '\0')
	{
		if (size_c > 1)
		{
			size_c--;
			dst[count_dst] = src[i];
			count_dst++;
		}
		i++;
	}
	dst[count_dst] = '\0';
	return (j + (&src[i] - src));
}
