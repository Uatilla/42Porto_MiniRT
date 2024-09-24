/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mods_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:48:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/22 16:36:10 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Calculates the cofactor.
/// @param mrt Main structure.
/// @param mtx Mtx to calculate.
/// @param row Row to be removed from the submtx.
/// @param col Col to be removed from the submtx.
/// @return Return the cofactor of the give matrix.
float	cofactor(t_minirt *mrt, t_matrix *mtx, int row, int col)
{
	if ((row + col) % 2 == 0)
		return (minor(mrt, mtx, row, col));
	else
		return (minor(mrt, mtx, row, col) * -1);
}

/// @brief Calculates the inverse matrix.
/// @param mrt Main structure.
/// @param mtx Matrix to find the inverse.
/// @return If there is no determinant == NULL, otherwise a new mtx.
t_matrix	*mtx_inverse(t_minirt *mrt, t_matrix *mtx)
{
	t_matrix	*mtx_res;
	t_matrix	*mtx_trans;
	float		determ;
	int			row;
	int			col;

	determ = determinant(mrt, mtx);
	if (determ == 0)
		return (NULL);
	mtx_res = mtx_create(mrt, mtx->rows, mtx->cols);
	if (!mtx_res)
		clean_matrix(mrt, mtx_res, errno);
	row = -1;
	while (++row < mtx->rows)
	{
		col = -1;
		while (++col < mtx->cols)
			mtx_res->mtx[row][col] = cofactor(mrt, mtx, row, col) / determ;
	}
	mtx_trans = mtx_transpose(mrt, mtx_res);
	clean_matrix(mrt, mtx_res, 0);
	return (mtx_trans);
}

/// @brief Adds a tuple into a mtx on column 3.(NO mem)
/// @param mtx Mtx to be translated.
/// @param tup_transl Tuple that will have its values add.
void	mtx_translation(t_matrix *mtx, t_tuple *tup_transl)
{
	int			row;
	float		*tup_arr;

	tup_arr = (float *)tup_transl;
	row = -1;
	while (++row < 3)
		mtx->mtx[row][3] = tup_arr[row];
}

/// @brief Add a tuple into a mtx on identity pos [0][0], [1][1]...
/// @param mtx Mtx to be scaled.
/// @param tup_scale Tuple that will scale the matrix.
void	mtx_scaling(t_matrix *mtx, t_tuple *tup_scale)
{
	int			row;
	int			col;
	float		*tup_arr;

	tup_arr = (float *)tup_scale;
	row = -1;
	while (++row < 3)
	{
		col = -1;
		while (++col < 3)
		{
			if (row == col)
				mtx->mtx[row][col] = tup_arr[row];
		}
	}
}
