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

void print_tetramino(const u_int16_t *tet)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", tet[i] >> j & 1);
		}
		printf("\n");
	}
	printf("\n");
}

void    print_map(const u_int16_t *array) {
	for (int i = 0; i < 16; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", array[i] >> j & 1);
		}
		printf("\n");
	}
}

void error(void)
{
    ft_putstr("error\n");
    exit(0);
}

u_int64_t bit_shift(u_int64_t tet)
{
	while ((9223512776490647552U & tet) == 0)
		tet <<= 1;
	while ((61440U & tet) == 0)
		tet >>= 16;
	return (tet);
}

u_int64_t    make_tetramino(const char *string)
{
    u_int64_t res;
    u_int64_t tmp;
	size_t i;

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
	res = reverse_bits_64(res);
	res = bit_shift(res);
    return (res);
}

int 	get_tetraminos(int fd, u_int64_t tetraminoarr[26])
{
	char tetrachr[22];
	int x;

	x = 0;
	ft_bzero(tetrachr, 22);

	while (read(fd, tetrachr, 21) > 0)
	{
		if (x == 27)
			error();
		tetraminoarr[x++] = make_tetramino(tetrachr);

	}
	if (tetrachr[21] == '\n')
		error();
	printf( "%d\n", x);
	return (x);
}

int sqrt_map(int count)
{
	int i;

	i = 1;
	count *= 4;
	while (i * i <= count)
		i++;
	return (i);
}

int fillit(u_int64_t tetramins[26], int size_map, u_int16_t map[16]) {
	uint64_t *tmp;
	int i;
	int k;

	i = 0;
	k = 0;
	tmp = map;
	if (tetramins[0] == 0)
		return (1);
	while (k <= size_map)
	{
		while (i <= size_map)
		{
			if ((*(u_int64_t *) (map) & tetramins[0]) != 0)
				break ;
			tetramins[0] >>= 1;
			i++;
		}
		if ((*(u_int64_t *) (map) & tetramins[0]) != 0)
			break ;
		tetramins[0] <<= i;
		map++;
		i = 0;
		k++;
	}
	if (k == size_map + 1 && i == size_map + 1)
		return (0);
	*(u_int64_t *) (map) ^= tetramins[0];
	if (fillit(&tetramins[1], size_map, tmp) == 1)
	else
	{
		if (i + 1 != size_map)
			fillit((tetramins[0] >>= 1), size_map, tmp);
		else
	}



}

int main(void)
{
	int fd;
	u_int64_t tetramino_array[26];
	u_int16_t map[16];
	int tetramino_count;
	int size_map;

	fd = open("test", O_RDONLY);
	tetramino_count = 0;
	while (tetramino_count != 26)
		tetramino_array[tetramino_count++] = 0;
    tetramino_count = get_tetraminos(fd, tetramino_array);
	size_map = sqrt_map(tetramino_count);
	fillit(tetramino_array, size_map, map);
    while (tetramino_count != -1)
    {
    	printf("%llu\n", tetramino_array[tetramino_count]);
    	print_tetramino((const u_int16_t *) &(tetramino_array[--tetramino_count]));
    }
	*(u_int64_t*)(map)  ^= tetramino_array[0];
	//*(u_int64_t*)(map)  ^= tetramino_array[1] >> 1;
    print_map(map);
    return 0;
}