/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mods_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:48:27 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/12 17:48:29 by uviana-a         ###   ########.fr       */
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
/// @return If there is no determinant == NULL.
t_matrix	*mtx_inverse(t_minirt *mrt, t_matrix *mtx)
{
	t_matrix	*mtx_res;
	float		determ;
	int		row;
	int		col;
	
  
	determ = determinant(mrt, mtx);
	if (compare_float(determ, 0))
        return (NULL);
    mtx_res = mtx_create(mrt, mtx->rows, mtx->cols);
	if (!mtx_res)
		clean_matrix(mrt, mtx_res, errno);
	row = -1;
	while (++row < mtx->rows)
	{
		col = -1;
		while (++col < mtx->cols) /*LOOK AT THIS FUNCTION VALIDAR COFACTOR*/
				printf("[%d][%d]: Cofa: %f Det: %f\n", row, col, cofactor(mrt, mtx, row, col), determ);
				//mtx_res->mtx[row][col] =  cofactor(mrt, mtx, row, col) / determ;
		printf("\n");
	}
	return (mtx_res);
}