/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tuples.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:21:50 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 15:21:53 by uviana-a         ###   ########.fr       */
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

/// @brief Operates a subtraction between two tuples.
/// @param a First tuple, also called as p1 (1st position).
/// @param b Second tuple, also called as p2 (2nd position).
/// @return The tuple result of the operation.
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
    return(res);
}

/// @brief Operates a subtraction between zero_tuple and tuple a.
/// @param a Tuple to be negated, it performs as the values were *(-1).
/// @return Tuple negated.
t_tuple negating_tuple(t_tuple *a)
{
    return(subtrac_tuples(&ZERO_TUPLE, a));
}