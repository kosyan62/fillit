/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:07:50 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 21:38:25 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount(char const *s, char c)
{
	size_t ptrnum;

	ptrnum = 1;
	while (*s != '\0')
	{
		if (*s != c)
			ptrnum++;
		while (*s != c && *s != '\0')
			s++;
		while (*s == c && *s != '\0')
			s++;
	}
	return (ptrnum);
}
