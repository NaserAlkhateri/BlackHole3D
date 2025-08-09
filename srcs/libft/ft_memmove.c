/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:23:20 by nalkhate          #+#    #+#             */
/*   Updated: 2023/11/16 19:31:13 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*buff_src;
	unsigned char	*buff_dst;

	buff_src = (unsigned char *) src;
	buff_dst = (unsigned char *) dst;
	i = 0;
	if (buff_src < buff_dst && buff_dst < buff_src + len)
	{
		buff_dst += len - 1;
		buff_src += len - 1;
		while (len > 0)
		{
			*buff_dst-- = *buff_src--;
			len--;
		}
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
