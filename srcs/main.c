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

bool	chk_mtx_line(float *matrix, int col)
{
	int	j;

	j = 0;
	while (j < col)
		{
			if (matrix[j] == '\0')
				return (false);
			j++;
		}
		if (j != col)
			return (false);
		return (true);
}


bool	chk_mtx_size(float **matrix, int rows, int col)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rows)
	{
		if(matrix[i] == NULL)
			return (false);
		
		if (!chk_mtx_line(matrix[i], col))
		{
			printf("FAIL\n");
			return (false);
		}
		i++;
	}
	if (i != rows)
		return(false);
	return (true);
}

float **creating_matrix(int rows, int col)
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
}

int main(void)
{
    int rows = 4;
    int cols = 4;

    // Allocate memory for the matrix
   float **mtx = creating_matrix(rows, cols);
    };
	if (!chk_mtx_size(mtx, rows, cols))
		printf("FALSE\n");
	else
		printf("TRUE\n");
    return 0;
}
