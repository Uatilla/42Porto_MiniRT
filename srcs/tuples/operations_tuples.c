/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tuples.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:21:50 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 19:19:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/// @brief Operates a sum between two tuples.
/// @param a First tuple, also called as p1 (1st position).
/// @param b Second tuple, also called as p2 (2nd position).
/// @return The tuple result of the operation.
t_tuple sum_tuples(t_tuple *a, t_tuple *b)
{
    t_tuple res;

    res.x = a->x + b->x;
    res.y = a->y + b->y;
    res.z = a->z + b->z;
    if (a->w != 999999 && b->w != 999999)
        res.w = a->w + b->w;
    else
        res.w = 999999;
    return(res);
}


t_tuple subtrac_tuples(t_tuple *a, t_tuple *b)
{
    t_tuple res;

    res.x = a->x - b->x;
    res.y = a->y - b->y;
    res.z = a->z - b->z;
    if (a->w != 999999 && b->w != 999999)
        res.w = a->w - b->w;
    else
        res.w = 999999;
	return (res);
}

/// @brief Find the intersection (scalar value) in a vector.
/// @param a Tuple to be multiplied.
/// @param sc Scalar value.
/// @return The tuple(point) in the scalar intersection.
t_tuple mult_tuple_scalar(t_tuple *a, float sc)
{
    t_tuple res;

    res.x = a->x * sc;
    res.y = a->y * sc;
    res.z = a->z * sc;
    if (a->w != 999999)
        res.w = a->w  * sc;
    else
        res.w = 999999;
    return(res);
}

/// @brief Find the intersection (scalar value) in a vector.
/// @param a Tuple to be divided.
/// @param sc Scalar value.
/// @return The tuple(point) in the scalar intersection.
t_tuple div_tuple_scalar(t_tuple *a, float sc)
{
    t_tuple res;

    res.x = a->x / sc;
    res.y = a->y / sc;
    res.z = a->z / sc;
    if (a->w != 999999)
        res.w = a->w  / sc;
    else
        res.w = 999999;
    return(res);
}

/// @brief Change vector size.
/// @param a Tuple a to be multiplied.
/// @param b Tuple b to be multiplied.
/// @return The size of the new vector.
float dot_product(t_tuple *a, t_tuple *b)
{
    t_tuple res;

    res.x = a->x * b->x;
    res.y = a->y * b->y;
    res.z = a->z * b->z;
    if (a->w != 999999)
        res.w = a->w  * b->w;
    else
        res.w = 999999;
    return(res.x + res.y + res.z + res.w);
}
