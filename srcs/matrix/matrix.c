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

/// @brief Check if the size of a matrix is equal rows and cols
/// @param mtx 
/// @param rows 
/// @param cols 
/// @return True or False
bool	mtx_chk_size(t_matrix *mtx, int rows, int cols)
{
	return (rows == mtx->rows && cols == mtx->rows);
}

/// @brief Create a new t_matrix.
/// @param data main structure.
/// @param rows number of rows.
/// @param cols number of columns.
/// @return A pointer to the t_matrix node.
t_matrix	*mtx_create(t_minirt *data, int rows, int cols)
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
void	mtx_fill(t_matrix *mtx)
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

void	mtx_print(t_matrix *mtx)//FUNCAO TEMPORARIA APENAS PARA FINS DE TESTE!!
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

/// @brief Compare the size of two matrix.
/// @param mtx_a 
/// @param mtx_b 
/// @return True or False
bool	mtx_size_compare(t_matrix *mtx_a, t_matrix *mtx_b)
{
	return(mtx_a->rows == mtx_b->rows && mtx_a->cols == mtx_b->cols);
}

/// @brief Compare the size and components in each matrix position.
/// @param mtx_a 
/// @param mtx_b 
/// @return True or False
bool	mtx_compare(t_matrix *mtx_a, t_matrix *mtx_b)
{
	int	i;
	int	j;

	if (mtx_size_compare(mtx_a, mtx_b))
	{
		i = -1;
		while (++i < mtx_a->rows)
		{
			j = -1;
			while (++j < mtx_a->cols)
			{
				if (!compare_float(mtx_a->mtx[i][j], mtx_b->mtx[i][j]))
					return (false);
			}
		}
		return (true);
	}
	else
		return (false);
}