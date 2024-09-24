/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_tuples_typ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:48:50 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/10 21:32:38 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	compare_float(float a, float b)
{
	return ((fabs(a - b) < EPSILON));
}

bool	is_point(t_tuple *tuple)
{
	return (compare_float(tuple->w, 1));
}

bool	is_vector(t_tuple *tuple)
{
	return (compare_float(tuple->w, 0));
}

bool	is_color(t_tuple *tuple)
{
	return (compare_float(tuple->w, 999999));
}

/// @brief Checks if all elements of the tuple are equal (X, Y, Z, W).
/// @param a First tuple to be compared.
/// @param b Second tuple to be compared.
/// @return True/False
bool	is_tuple_equal(t_tuple *a, t_tuple *b)
{
	return ((fabs(a->x - b->x) < EPSILON) \
		&& (fabs(a->y - b->y) < EPSILON) \
		&& (fabs(a->z - b->z) < EPSILON) \
		&& (fabs(a->w - b->w) < EPSILON));
}
