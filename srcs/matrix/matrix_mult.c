/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:49:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/10 17:49:59 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	get_mtx_value(t_matrix *mtx, int row, int col)
{
	return (mtx->mtx[row][col]);
}

/// @brief Multiple the elements of the matrix (mtx_a->row x mtx_b->col).
/// @param mtx_a 
/// @param mtx_b 
/// @param row Row from mtx_a to multiple.
/// @param col Col from mtx_b to multiple.
/// @return The product value of all elements.
float	mult_mtx_row_col(t_matrix *mtx_a, t_matrix *mtx_b, int row, int col)
{
	int		a_col;
	int		b_row;
	float	res;

	res = 0;
	a_col = -1;
	b_row = -1;
	while (++a_col < mtx_a->cols && ++b_row < mtx_b->rows)
		res += mtx_a->mtx[row][a_col] * mtx_b->mtx[b_row][col];
	return (res);
}

/// @brief Multiple the components of two matrix.
/// @param mtx_a 
/// @param mtx_b 
/// @return If matrix sizes are different (rows and cols), return NULL.
t_matrix	*mtx_multiply(t_minirt *mrt, t_matrix *mtx_a, t_matrix *mtx_b)
{
	t_matrix	*mtx_res;
	int			row;
	int			col;

	(void)mrt;
	if (!mtx_size_compare(mtx_a, mtx_b))
		return (NULL);
	mtx_res = mtx_create(mrt, mtx_a->rows, mtx_a->cols);
	row = -1;
	while (++row < mtx_res->rows)
	{
		col = -1;
		while (++col < mtx_res->cols)
			mtx_res->mtx[row][col] = mult_mtx_row_col(mtx_a, mtx_b, row, col);
	}
	return (mtx_res);
}
