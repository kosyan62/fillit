/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:59:12 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 22:03:15 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** sqrt_map - Calculates initial minimum map size for given tetramino count
** @count: Number of tetraminos to fit
** Returns: Minimum square size needed (assuming no gaps)
** Side effects: None
** 
** Algorithm: Since each tetramino has 4 blocks, we need at least
** count * 4 total blocks. Find the smallest square that can fit them.
*/
int			sqrt_map(int count)
{
	int i;

	i = 1;
	count *= 4;  /* Each tetramino has 4 blocks */
	while (i * i < count)
		i++;
	return (i);
}

/*
** fill_map_alpha - Converts tetramino bit pattern to alphabet characters
** @tet: Pointer to 4 rows of 16-bit values representing the tetramino
** @map: Pointer to character map where tetramino will be written
** @map_size: Size of the map (for row calculations)
** Returns: void
** Side effects: Modifies map content and increments static letter counter
** 
** Algorithm: For each row of the tetramino, check each bit position.
** If bit is set, place the current letter (A, B, C, etc.) in the map.
*/
void		fill_map_alpha(uint16_t *tet, char *map, int map_size)
{
	static char	letter;  /* Static counter for tetramino letters (A, B, C...) */
	int			i;
	int			j;

	i = 0;
	while (i != 4)  /* Process 4 rows of tetramino */
	{
		j = 16;
		while (j != 0)  /* Check each bit position (right to left) */
		{
			if ((tet[i] >> (j - 1) & 1) == 1)  /* If bit is set */
				map[16 - j] = letter + 65;      /* Place letter (A=65, B=66, etc.) */
			j--;
		}
		map = map + map_size;  /* Move to next row in map */
		i++;
	}
	letter++;  /* Move to next letter for next tetramino */
}

/*
** print_ready_map - Prints the solved map to stdout
** @map_chr: Character array containing the solution
** @map_size: Size of the square map
** Returns: void
** Side effects: Prints map to stdout with newlines
** 
** Algorithm: Print each character followed by newline at end of each row
*/
void		print_ready_map(char map_chr[300], int map_size)
{
	int i;

	i = 1;
	while (map_chr[i] != 0)
	{
		ft_putchar(map_chr[i - 1]);
		if (i % map_size == 0)  /* End of row */
			ft_putchar('\n');
		i++;
	}
}

/*
** fill_ready_map - Converts solution to printable character map
** @map_size: Size of the square map
** @tet: Array of tetraminos with their final positions
** Returns: void
** Side effects: Calls print_ready_map to output the solution
** 
** Algorithm: Initialize map with dots, then place each tetramino
** at its solved position using fill_map_alpha
*/
void		fill_ready_map(int map_size, t_tetramino *tet)
{
	char	map_chr[300];  /* Character representation of the map */
	int		i;
	int		x;

	i = 0;
	x = 0;
	ft_bzero(map_chr, 299);
	/* Initialize entire map with dots */
	while (i != map_size * map_size + 1)
		map_chr[i++] = '.';
	i = 0;
	/* Place each tetramino at its solved position */
	while (tet[x].cont != 0)  /* Process each tetramino */
	{
		if (i == tet[x].x + (tet[x].y * map_size))  /* Found tetramino position */
		{
			fill_map_alpha((uint16_t *)&(tet[x].cont), &map_chr[i], map_size);
			x++;  /* Move to next tetramino */
			i = 0;  /* Reset position search */
		}
		else
			i++;
	}
	print_ready_map(map_chr, map_size);
}

/*
** main - Entry point of the fillit program
** @argc: Number of command line arguments
** @argv: Array of command line arguments
** Returns: 0 on success
** Side effects: Reads file, solves tetramino puzzle, prints solution
** 
** Algorithm:
** 1. Validate command line arguments
** 2. Open and read tetraminos from file
** 3. Calculate initial map size
** 4. Use backtracking to find solution, increasing map size if needed
** 5. Print the solution
*/
int			main(int argc, char **argv)
{
	int			fd;
	t_tetramino	tetramino_array[26];  /* Max 26 tetraminos (A-Z) */
	t_map		map;

	if (argc != 2)  /* Must have exactly one argument (filename) */
		error();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)  /* File couldn't be opened */
		error();
	
	/* Initialize map array to zero */
	map.tetramino_count = 0;
	while (map.tetramino_count != 16)
	{
		map.cont[map.tetramino_count] = 0;
		map.tetramino_count++;
	}
	
	/* Initialize tetramino array to zero */
	map.tetramino_count = 0;
	while (map.tetramino_count != 27)
		tetramino_array[map.tetramino_count++].cont = 0;
	
	/* Read tetraminos from file */
	map.tetramino_count = get_tetraminos(fd, tetramino_array);
	
	/* Calculate initial map size based on tetramino count */
	map.size = sqrt_map(map.tetramino_count);
	
	/* Try to solve with current map size, increase if no solution found */
	while (fillit(tetramino_array, &map) != 1)
		map.size++;
	
	/* Print the solution */
	fill_ready_map(map.size, tetramino_array);
	return (0);
}
