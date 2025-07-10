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

/*
** error - Prints error message and exits program
** Returns: void (never returns)
** Side effects: Prints "error\n" to stdout and exits with code 0
** 
** Used throughout the program when invalid input is detected
*/
void		error(void)
{
	ft_putstr("error\n");
	exit(0);
}

/*
** check_tetramino - Validates tetramino against known valid patterns
** @res: 64-bit tetramino representation to validate
** Returns: void
** Side effects: Calls error() if pattern is invalid
** 
** Algorithm: Compare against hardcoded list of all 19 valid tetramino patterns
** Each pattern represents a unique tetramino shape in normalized form
** (positioned at top-left corner of 4x4 grid)
*/
void		check_tetramino(uint64_t res)
{
	if (res != 9223512776490647552U &&  /* I-piece vertical */
		res != 61440 &&                  /* I-piece horizontal */
		res != 536928256 &&              /* O-piece (square) */
		res != 3758104576 &&             /* T-piece rotation 1 */
		res != 3758129152 &&             /* T-piece rotation 2 */
		res != 2147540992 &&             /* T-piece rotation 3 */
		res != 70369817968640 &&         /* T-piece rotation 4 */
		res != 140739635888128 &&        /* S-piece rotation 1 */
		res != 211107306291200 &&        /* S-piece rotation 2 */
		res != 211108380049408 &&        /* Z-piece rotation 1 */
		res != 1073799168 &&             /* Z-piece rotation 2 */
		res != 3758112768 &&             /* L-piece rotation 1 */
		res != 70371965419520 &&         /* L-piece rotation 2 */
		res != 140740709613568 &&        /* L-piece rotation 3 */
		res != 3221274624 &&             /* L-piece rotation 4 */
		res != 1610661888 &&             /* J-piece rotation 1 */
		res != 3221250048 &&             /* J-piece rotation 2 */
		res != 70371965435904 &&         /* J-piece rotation 3 */
		res != 140740709597184)          /* J-piece rotation 4 */
		error();
}

/*
** reverse_bits_64 - Reverses the bit order of a 64-bit integer
** @tet: 64-bit integer to reverse
** Returns: 64-bit integer with bits in reverse order
** Side effects: None
** 
** Algorithm: Extract each bit from right to left, shift result left,
** and add the extracted bit. Used for bit manipulation during parsing.
*/
uint64_t reverse_bits_64(uint64_t tet)
{
	uint64_t res;
	int i;

	res = 0;
	i = 0;
	while (i < 64)
	{
		res <<= 1;           /* Shift result left */
		res |= (tet & 1);    /* Add rightmost bit of tet */
		tet >>= 1;           /* Shift tet right */
		i++;
	}
	return (res);
}

/*
** bit_shift - Normalizes tetramino to top-left corner position
** @tet: Raw tetramino bit pattern
** Returns: Normalized tetramino pattern positioned at top-left
** Side effects: Calls error() if pattern is invalid
** 
** Algorithm: 
** 1. Reverse bits to correct orientation
** 2. Shift left until leftmost column has at least one bit
** 3. Shift up until topmost row has at least one bit
** 4. Validate against known patterns
*/
uint64_t	bit_shift(uint64_t tet)
{
	tet = reverse_bits_64(tet);
	if (tet == 0)  /* Empty tetramino */
		error();
	
	/* Shift left until leftmost column (mask: 9223512776490647552U) has bits */
	while ((9223512776490647552U & tet) == 0)
		tet <<= 1;
	
	/* Shift up until topmost row (mask: 61440U) has bits */
	while ((61440U & tet) == 0)
		tet >>= 16;
	
	check_tetramino(tet);  /* Validate normalized pattern */
	return (tet);
}

/*
** tetra_width - Calculates width of tetramino in grid units
** @tet: Tetramino bit pattern
** Returns: Width in grid units (1-4)
** Side effects: None
** 
** Algorithm: Count how many columns from left contain at least one bit
** Uses leftmost column mask and shifts left until no bits remain
*/
int			tetra_width(uint64_t tet)
{
	int w;

	w = 0;
	/* Count columns with bits using leftmost column mask */
	while ((9223512776490647552U & tet) != 0)
	{
		tet <<= 1;  /* Shift left to check next column */
		w++;
	}
	return (w);
}

/*
** tetra_height - Calculates height of tetramino in grid units
** @tet: Tetramino bit pattern
** Returns: Height in grid units (1-4)
** Side effects: None
** 
** Algorithm: Count how many rows from top contain at least one bit
** Uses topmost row mask and shifts down until no bits remain
*/
int			tetra_height(uint64_t tet)
{
	int l;

	l = 0;
	/* Count rows with bits using topmost row mask */
	while ((61440U & tet) != 0)
	{
		tet >>= 16;  /* Shift down to check next row */
		l++;
	}
	return (l);
}
