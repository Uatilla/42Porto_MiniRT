/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 19:15:50 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool	chk_mtx_size(float matrix[4][4], int size)
{
	int	i;
	int	j;
	int chk_row;
	int	chk_col;

	chk_row = 0;
	chk_col = 0;
	i = -1;
	while (matrix[++i])
	{
		j = -1;
		chk_row++;
		chk_col = 0;
		while (matrix[i][++j])
		{
			chk_col++;
			printf("");
		}
		if (chk_col < size)
		{
			printf("Col: %d\n", chk_col);
			return (false);
		}
	}
	if (chk_row < size)
		return (false);
	return (true);
}

int main(void)
{
	float mtx[4][4] = {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}
    };
	if (!chk_mtx_size(mtx, 4))
		printf("False\n");
    return (0);
}
