/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 23:12:40 by mgena             #+#    #+#             */
/*   Updated: 2019/09/20 12:00:55 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t srclen;
	size_t k;
	size_t dstlen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen > size)
		return (size + srclen);
	k = 0;
	while (k + dstlen < size - 1 && src[k] != '\0')
	{
		dst[k + dstlen] = src[k];
		k++;
	}
	dst[k + dstlen] = 0;
	return (srclen + dstlen);
}
