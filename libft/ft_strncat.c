/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:14:10 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 21:38:25 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*res;

	res = s1;
	i = 0;
	while (*s1 != '\0')
		s1++;
	while (i < n && s2[i] != 0)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = 0;
	return (res);
}
