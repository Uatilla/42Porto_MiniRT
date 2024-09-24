/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_modifications.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:49:24 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/12 11:49:26 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Takes on matrix and transpose its positions.
/// @param mrt Main structure.
/// @param mtx Matrix that will be transposed. (Memory freed before return).
/// @return If failed to allocate memory, call clean_matrix with error num.
t_matrix	*mtx_transpose(t_minirt *mrt, t_matrix *mtx)
{
	t_matrix	*mtx_res;
	int			i;
	int			j;
	int			k;

	mtx_res = mtx_create(mrt, mtx->rows, mtx->cols);
	if (!mtx_res)
		clean_matrix(mrt, mtx_res, errno);
	i = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		while (++j < mtx->cols)
			mtx_res->mtx[i][j] = mtx->mtx[j][i];
	}
	return (mtx_res);
}

void	copy_val_to_submtx(t_matrix *mtx, t_matrix *submtx,
			int excl_row, int excl_col)
{
	int			i;
	int			j;
	int			k;
	int			w;

	i = -1;
	k = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		w = -1;
		if (i == excl_row)
			continue ;
		k++;
		while (++j < mtx->cols)
		{
			if (j == excl_col)
				continue ;
			w++;
			submtx->mtx[k][w] = mtx->mtx[i][j];
		}
	}
}

/// @brief Extracts the submtx a row/col from a mtx.
/// @param mrt Main structure.
/// @param mtx Matrix to have rows and columns removed (Memory not freed).
/// @param excl_row Row index to be removed.
/// @param excl_col Col index to be removed.
/// @return Pointer to submtx, if the index > mtx size, it returns NULL.
t_matrix	*submatrix(t_minirt *mrt, t_matrix *mtx, int excl_row, int excl_col)
{
	t_matrix	*sub_mtx_res;

	if (excl_row >= mtx->rows || excl_col >= mtx->cols)
		return (NULL);
	sub_mtx_res = mtx_create(mrt, mtx->rows - 1, mtx->cols - 1);
	if (!sub_mtx_res)
		clean_matrix(mrt, sub_mtx_res, errno);
	copy_val_to_submtx(mtx, sub_mtx_res, excl_row, excl_col);
	return (sub_mtx_res);
}

/// @brief Find a matrix determinant (THIS FUNCTION CAN'T CHECK MTX SIZE)
/// @param mtx This matrix MUST BE square (2x2, 3x3 or 4x4).
/// @return Determinant of the matrix;
float	determinant(t_minirt *mrt, t_matrix *mtx)
{
	float	determ;
	int		i;
	int		col;

	(void)mrt;
	determ = 0;
	i = -1;
	if (mtx->rows == 2 && mtx->cols == 2)
		return ((mtx->mtx[0][0] * mtx->mtx[1][1]) -
				(mtx->mtx[0][1] * mtx->mtx[1][0]));
	else
	{
		col = -1;
		while (++col < mtx->cols)
			determ += mtx->mtx[0][col] * cofactor(mrt, mtx, 0, col);
	}
	return (determ);
}

/// @brief It calculates the minor of the mtx.
/// @param mrt Main structure.
/// @param mtx Mtx to calculate its minor.
/// @param row Row of the submtx that will be removed. 
/// @param col Col of the submtx that will be removed. 
/// @return The submatrix minor of given mtx.
float	minor(t_minirt *mrt, t_matrix *mtx, int row, int col)
{
	t_matrix	*submtx;
	float		determ;

	submtx = submatrix(mrt, mtx, row, col);
	determ = determinant(mrt, submtx);
	if (submtx)
		clean_matrix(mrt, submtx, 0);
	return (determ);
}
