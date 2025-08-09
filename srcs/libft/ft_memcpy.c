/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:54:52 by nalkhate          #+#    #+#             */
/*   Updated: 2023/11/16 19:26:25 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*buff1;
	unsigned char		*buff2;

	buff1 = (unsigned char *) dst;
	buff2 = (unsigned char *) src;
	i = 0;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		buff1[i] = buff2[i];
		i++;
	}
	return (dst);
}
