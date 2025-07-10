/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetramino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:07:38 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 21:38:38 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** make_tetramino - Parses 4x4 grid string into 64-bit representation
** @string: 19-character string representing 4x4 grid with newlines
** Returns: 64-bit normalized tetramino pattern
** Side effects: Calls error() if invalid format
** 
** Algorithm: Convert 4x4 grid to bit pattern, then normalize position
** Each '#' becomes a 1 bit, each '.' becomes a 0 bit
** Format: 4 rows of 4 chars each, separated by newlines
*/
uint64_t	make_tetramino(const char *string)
{
	size_t		i;
	uint64_t	res;
	uint64_t	tmp;

	i = 0;
	tmp = 0;
	res = 0;
	while (i != 19)  /* Process 19 characters (4*4 + 3 newlines) */
	{
		/* Validate character format */
		if (string[i] != '#' && string[i] != '.' && string[i] != '\n')
			error();
		if (string[i] == '#')
			res |= (1 << tmp);  /* Set bit for tetramino block */
		tmp++;
		if (string[i] == '\n')  /* End of row */
		{
			res <<= 16;  /* Move to next 16-bit row */
			tmp = 0;     /* Reset bit position */
		}
		i++;
	}
	/* Validate end of tetramino (should be newline or end of file) */
	if (string[20] == '.' || string[20] == '#' || string[0] == 0)
		error();
	return (bit_shift(res));  /* Normalize to top-left position */
}

/*
** get_tetraminos - Reads all tetraminos from file descriptor
** @fd: File descriptor to read from
** @tetraminoarr: Array to store parsed tetraminos (max 26)
** Returns: Number of tetraminos successfully read
** Side effects: Calls error() if invalid format or too many tetraminos
** 
** Algorithm: Read 21 bytes at a time (4x4 grid + 3 newlines + separator)
** Parse each block, calculate dimensions, validate format
*/
int			get_tetraminos(int fd, t_tetramino tetraminoarr[26])
{
	char	tetrachr[22];  /* Buffer for tetramino data */
	char	lastchar;      /* Last character read (for validation) */
	int		x;

	x = 0;
	ft_bzero(tetrachr, 22);
	while (read(fd, tetrachr, 21) > 0)  /* Read 21 bytes per tetramino */
	{
		if (x == 26)  /* Maximum 26 tetraminos allowed */
			error();
		/* Parse tetramino and store in array */
		tetraminoarr[x].cont = make_tetramino(tetrachr);
		tetraminoarr[x].width = tetra_width(tetraminoarr[x].cont);
		tetraminoarr[x].height = tetra_height(tetraminoarr[x].cont);
		lastchar = tetrachr[20];  /* Store separator character */
		ft_bzero(tetrachr, 22);
		x++;
	}
	if (x == 0)  /* No tetraminos read */
		error();
	if (lastchar != '\0')  /* Last tetramino should end with null */
		error();
	return (x);
}

/*
** get_pos - Stores position coordinates in tetramino structure
** @i: Array containing [x, y] coordinates
** @tet: Tetramino structure to update
** Returns: void
** Side effects: Updates tet->x and tet->y
** 
** Simple utility function to set tetramino position
*/
void		get_pos(int i[2], t_tetramino *tet)
{
	tet->x = i[0];
	tet->y = i[1];
}

/*
** fillit - Main backtracking algorithm for tetramino placement
** @tet: Pointer to current tetramino in array (recursive parameter)
** @map: Map structure containing the game board
** Returns: 1 if successful placement found, 0 if no solution
** Side effects: Modifies map content temporarily during backtracking
** 
** BACKTRACKING ALGORITHM:
** 1. Base case: If current tetramino is empty (cont == 0), all pieces placed
** 2. Try each position on the map from top-left to bottom-right
** 3. For each position, check if tetramino fits without collision
** 4. If it fits: place it, recursively try next tetramino
** 5. If recursion succeeds: solution found, store position and return
** 6. If recursion fails: backtrack by removing tetramino and try next position
** 7. If no position works: return failure
*/
int			fillit(t_tetramino *tet, t_map *map)
{
	int i[2];  /* Position coordinates: [x, y] */

	i[1] = 0;  /* Start from top row */
	
	/* BASE CASE: If current tetramino is empty, all pieces have been placed */
	if ((*tet).cont == 0)
		return (1);
	
	/* Try each row where tetramino can fit */
	while (i[1] + (*tet).height <= map->size)
	{
		i[0] = 0;  /* Start from leftmost column */
		
		/* Try each column where tetramino can fit */
		while (i[0] + (*tet).width <= map->size)
		{
			/* COLLISION CHECK: Use bitwise AND to check if position is free */
			/* If result is 0, no collision - position is available */
			if ((*(uint64_t *)(map->cont + i[1]) & (*tet).cont >> i[0]) == 0)
			{
				/* PLACE TETRAMINO: Use XOR to place tetramino on map */
				*(uint64_t *)(map->cont + i[1]) ^= (*tet).cont >> i[0];
				
				/* RECURSIVE CALL: Try to place next tetramino */
				if (fillit(tet + 1, map) == 1)
				{
					/* SUCCESS: Solution found, store position and return */
					get_pos(i, tet);
					return (1);
				}
				
				/* BACKTRACK: Remove tetramino from map (XOR again) */
				*(uint64_t *)(map->cont + i[1]) ^= (*tet).cont >> i[0];
			}
			i[0]++;  /* Move to next column */
		}
		i[1]++;  /* Move to next row */
	}
	
	/* NO SOLUTION: All positions tried, no valid placement found */
	return (0);
}
