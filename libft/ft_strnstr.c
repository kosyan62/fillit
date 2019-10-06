/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:42:19 by mgena             #+#    #+#             */
/*   Updated: 2019/09/11 20:16:04 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	if (*needle == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0' && i != len)
	{
		while ((haystack[i + k] == needle[k]) && (*needle != '\0') \
				&& (haystack[i + k] != '\0') && i + k != len)
			k++;
		if (needle[k] == '\0')
			return (&((char*)haystack)[i]);
		else
			k = 0;
		i++;
	}
	return (NULL);
}
