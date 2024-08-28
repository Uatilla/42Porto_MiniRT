/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:49:57 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/18 22:16:08 by Jburlama         ###   ########.fr       */
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

/// @brief Allocate memory for a new mtx and put the values:(mtx_a * mtx_b).
/// @param mtx_a First matrix to multiply.
/// @param mtx_b Second matrix to multiply.
/// @return If mtx sizes are diff, return NULL without any memory allocation.
t_matrix	*mtx_multiply(t_minirt *mrt, t_matrix *mtx_a, t_matrix *mtx_b)
{
	t_matrix	*mtx_res;
	int			row;
	int			col;

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
	clean_matrix(mrt, mtx_b, 0);
	clean_matrix(mrt, mtx_a, 0);
	return (mtx_res);
}

/// @brief Multiple a matrix row with a tuple position.
/// @param mtx_a 
/// @param tup 
/// @param row 
/// @return return a float that represent the multiplication.
float	mult_mtx_row_tuple(t_matrix *mtx_a, t_tuple *tup, int row)
{
	float	res;
	int		i;
	float	*ptr;

	res = 0;
	i = -1;
	ptr = (float *)tup;
	while (++i < mtx_a->cols)
		res += mtx_a->mtx[row][i] * ptr[i];
	return (res);
}

/// @brief Multiple a matrix with a tuple.
/// @param mtx_a Matrix to be multiplied.
/// @param tup Tuple to be multiplied.
/// @return A new tuple with the multiplication done.
t_tuple	mtx_mult_tuple(t_matrix *mtx_a, t_tuple *tup)
{
	t_tuple	tup_res;
	float	*ptr_res;
	int		i;

	ptr_res = (float *)&tup_res;
	i = -1;
	while (++i < mtx_a->rows)
		ptr_res[i] = mult_mtx_row_tuple(mtx_a, tup, i);
	return (tup_res);
}
