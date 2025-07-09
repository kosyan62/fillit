/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:04:30 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 21:38:25 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		error(void)
{
	ft_putstr("error\n");
	exit(0);
}

void		check_tetramino(uint64_t res)
{
	if (res != 9223512776490647552U &&
		res != 61440 &&
		res != 536928256 &&
		res != 3758104576 &&
		res != 3758129152 &&
		res != 2147540992 &&
		res != 70369817968640 &&
		res != 140739635888128 &&
		res != 211107306291200 &&
		res != 211108380049408 &&
		res != 1073799168 &&
		res != 3758112768 &&
		res != 70371965419520 &&
		res != 140740709613568 &&
		res != 3221274624 &&
		res != 1610661888 &&
		res != 3221250048 &&
		res != 70371965435904 &&
		res != 140740709597184)
		error();
}

uint64_t reverse_bits_64(uint64_t tet)
{
	uint64_t res;
	int i;

	res = 0;
	i = 0;
	while (i < 64)
	{
		res <<= 1;
		res |= (tet & 1);
		tet >>= 1;
		i++;
	}
	return (res);
}

uint64_t	bit_shift(uint64_t tet)
{
	tet = reverse_bits_64(tet);
	if (tet == 0)
		error();
	while ((9223512776490647552U & tet) == 0)
		tet <<= 1;
	while ((61440U & tet) == 0)
		tet >>= 16;
	check_tetramino(tet);
	return (tet);
}

int			tetra_width(uint64_t tet)
{
	int w;

	w = 0;
	while ((9223512776490647552U & tet) != 0)
	{
		tet <<= 1;
		w++;
	}
	return (w);
}

int			tetra_height(uint64_t tet)
{
	int l;

	l = 0;
	while ((61440U & tet) != 0)
	{
		tet >>= 16;
		l++;
	}
	return (l);
}
