/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:02:06 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/18 21:06:09 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_matrix	*view_transformation(t_point *from, t_point *to, t_vector *up)
{
	t_view		view;
	t_matrix	*orientation;
	t_matrix	*trans;
	t_matrix	*ret;

	view.forward = subtrac_tuples(to, from);
	view.forward = normalize(&view.forward);
	view.upn = normalize(up);
	view.left = cross_product(&view.forward, &view.upn);
	view.true_uper = cross_product(&view.left, &view.forward);
	orientation = view_orientation(&view.left, &view.true_uper, &view.forward);
	trans = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(trans);
	mtx_translation(trans, &(t_point){-from->x, -from->y, -from->z, 1});
	ret = mtx_multiply(NULL, orientation, trans);
	return (ret);
}

t_matrix	*view_orientation(t_vector *left, t_vector *up, t_vector *forward)
{
	t_matrix	*orientation;

	orientation = mtx_create(NULL, 4, 4);
	orientation->mtx[0][0] = left->x;
	orientation->mtx[0][1] = left->y;
	orientation->mtx[0][2] = left->z;
	orientation->mtx[1][0] = up->x;
	orientation->mtx[1][1] = up->y;
	orientation->mtx[1][2] = up->z;
	orientation->mtx[2][0] = -forward->x;
	orientation->mtx[2][1] = -forward->y;
	orientation->mtx[2][2] = -forward->z;
	orientation->mtx[3][3] = 1;
	return (orientation);
}
