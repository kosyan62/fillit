/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:39:51 by mgena             #+#    #+#             */
/*   Updated: 2019/09/30 18:34:30 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

uint64_t	reverse_bits(uint64_t tet)
{
	int i;
	uint64_t x = 0;
	uint64_t res = 0;

	x = 1;
	i = 63;

	while (i > 0)
	{
		res = res | ((tet & x) << i);
		x = x << 1;
		i -= 2;
	}
	i = 1;
	while (i < 64)
	{
		res = res | ((tet & x) >> i);
		x = x << 1;
		i += 2;
	}
	return (res);
}


void print_tetramino(uint16_t *tet)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", (tet[i] >> j) & 1);
		}
		printf("\n");
	}
	printf("\n");
}

void    print_map(uint16_t *array) {
	for (int i = 0; i < 16; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", (array[i] >> j) & 1);
		}
		printf("\n");
	}
}

void error(void)
{
    ft_putstr("error\n");
    exit(0);
}

uint64_t bit_shift(uint64_t tet)
{
	while ((9223512776490647552 & tet) == 0)
		tet = tet << 1;
	while ((61440 & tet) == 0)
		tet = tet >> 16;
	return (tet);
}

uint64_t    make_tetramino(char *string)
{
    uint64_t res;
    size_t i;
    uint64_t tmp;

    i = 0;
    tmp = 0;
    res = 0;
    while (i != 19)
    {
        if (string[i] == '#')
            res = res | (1 << tmp);
        if (string[i++] == '\n')
        {
            res = res << 16;
            tmp = 0;

        }
        else
	        tmp++;
    }
	res = reverse_bits(res);
	res = bit_shift(res);
    return (res);
}

void get_tetraminos(int fd, uint64_t tetraminoarr[26])
{
	char *line;
	char tetrachr[22];
	int i;
	int x;
	int ret;

	i = 0;
	x = 0;
	line = NULL;
	ft_bzero(tetrachr, 22);

	while ((ret = read(fd, tetrachr, 21)) > 0)
	{
		tetraminoarr[x++] = make_tetramino(tetrachr);
	}
	if (tetrachr[21] == '\n')
		error();
}

int main(void)
{
	int fd;
	char *line;
	uint64_t tetramino_array[26];
	uint16_t map[16];
	int i = 0;

	fd = open("test", O_RDONLY);
    get_tetraminos(fd, tetramino_array);
    while (i != 5)
    {
    	printf("%llu\n", tetramino_array[i]);
    	print_tetramino(&(tetramino_array[i++]));
    }
//	*(uint64_t*)map = *(uint64_t*)(map + 2) ^ tetramino_array[0];
	printf("%llu\n", tetramino_array[1]);
	*(uint64_t*)(map)  ^= tetramino_array[1];
    print_map(map);
    return 0;
}