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

bool	chk_mtx_size(float **matrix, int rows, int col)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		printf("ROW: %d\n", i);
		j = 0;
		while (j < col)
		{
			printf("%f\t", matrix[i][j]);
			printf("COL: %d\t", j);
			j++;
		}
		if (j == col && matrix[i][j] != 0)
			return (false);
		printf("\n");
		i++;
	}
	if (i == rows && matrix[i][j] == 0)
			return (false);
	return (true);
}

/*float **creating_matrix(int rows, int col)
{
	float	**mtx_ret;
	int		curr_row;

	curr_row = 0;

	mtx_ret = malloc(rows * sizeof(float *));
	//if (!mtx_ret)
	//	return 
	while (curr_row < rows)
	{
		mtx_ret[curr_row] = malloc(col * sizeof(float *));
		//if (!mtx_ret)
		//return 
		curr_row++;
	}
	return(mtx_ret);
}*/

int main(void)
{
    int rows = 4;
    int cols = 4;

    // Allocate memory for the matrix
    float **mtx = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; ++i) {
        mtx[i] = (float *)malloc(cols * sizeof(float));
    }
	if (!chk_mtx_size(mtx, 4, cols))
		printf("FALSE\n");
	else
		printf("TRUE\n");
    // Free the allocated memory
    for (int i = 0; i < rows; ++i) {
        free(mtx[i]);
    }
    free(mtx);

    return 0;
}
