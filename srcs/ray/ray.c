/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:10:00 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/03 17:42:13 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * Finds the t position along the ray.
 * P(t) = O + Dt
 * O -> the ray origim
 * D -> Normalize direction
 * t -> units along the ray
 *
 * returns a the point t along the ray
*/
t_tuple	position(t_ray *ray, float t)
{
	t_tuple	ret;

	ret = mult_tuple_scalar(&ray->direction, t);
	ret = sum_tuples(&ret, &ray->origin);
	return (ret);
}
