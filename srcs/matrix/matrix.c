/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:57:14 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/07 19:57:18 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	check_mtx_size(t_matrix *mtx, int rows, int cols)
{
	return (rows == mtx->rows && cols == mtx->rows);
}

t_matrix	*creating_matrix(t_minirt *data, int rows, int cols)
{
	t_matrix	*mtx_struct;
	int			curr_row;

	curr_row = 0;
	mtx_struct = (t_matrix *)ft_calloc(sizeof(t_matrix), 1);
	if (!mtx_struct)
		clean_matrix(data, mtx_struct, errno);
	mtx_struct->rows = rows;
	mtx_struct->cols = cols;
	mtx_struct->mtx = (float **)ft_calloc(sizeof(float *), rows);
	if (!mtx_struct->mtx)
		clean_matrix(data, mtx_struct, errno);
	while (curr_row < rows)
	{
		mtx_struct->mtx[curr_row] = (float *)ft_calloc(sizeof(float), cols);
		if (!mtx_struct->mtx[curr_row])
			clean_matrix(data, mtx_struct, errno);
		curr_row++;
	}
	return (mtx_struct);
}

//FUNCAO TEMPORARIA APENAS PARA FINS DE TESTE!!
void	fill_mtx(t_matrix *mtx)
{
	int	value;
	int	i;
	int	j;

	printf("\n\nmatrix.c/fill_mtx(): ATENCAO ESSA \
		FUNCAO SO TEM FINALIDADE DE TESTE.\n\n");
	value = 0;
	i = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		while (++j < mtx->cols)
		{
			mtx->mtx[i][j] = value++;
		}
	}
}

void	print_mtx(t_matrix *mtx)//FUNCAO TEMPORARIA APENAS PARA FINS DE TESTE!!
{
	int	value;
	int	i;
	int	j;

	printf("\n\nmatrix.c/print_mtx(): ATENCAO ESSA \
		FUNCAO SO TEM FINALIDADE DE TESTE.\n\n");
	value = 0;
	i = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		while (++j < mtx->cols)
		{
			printf("%f | ", mtx->mtx[i][j]);
		}
		printf("\n");
	}
}
