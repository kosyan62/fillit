/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:56:44 by mgena             #+#    #+#             */
/*   Updated: 2019/09/11 17:56:47 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	char	*tmp;
	size_t	i;

	i = ft_strlen(s1) + 1;
	tmp = (char*)malloc(i);
	if (tmp == NULL)
		return (NULL);
	res = tmp;
	while (i != 0)
	{
		*tmp = *s1;
		tmp++;
		s1++;
		i--;
	}
	return (res);
}
