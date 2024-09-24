/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:52:57 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 16:58:18 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
*	returns the normal vector for any given object, for the world coordenates
*	point of view
*/
t_vector	normal_at(t_shape *obj, t_point *point, t_minirt *data)
{
	t_point		local_point;
	t_vector	local_normal;
	t_vector	world_normal;
	t_matrix	*transpose;

	local_point = mtx_mult_tuple(obj->mtx_inver, point);
	local_normal = local_normal_at(obj, &local_point);
	transpose = mtx_transpose(data, obj->mtx_inver);
	world_normal = mtx_mult_tuple(transpose, &local_normal);
	world_normal.w = 0;
	clean_matrix(data, transpose, 0);
	return (normalize(&world_normal));
}

/*
*	returns the normal vector for any given object, for the object coordenates
*	point of view
*/
t_vector	local_normal_at(t_shape *obj, t_point *local_point)
{
	t_vector	local_normal;

	if (obj->type == SP)
		local_normal = subtrac_tuples(local_point, &(t_point){0, 0, 0, 1});
	else if (obj->type == CY)
		local_normal = normal_at_cy(local_point, obj);
	else if (obj->type == PL)
		local_normal = (t_vector){0, 1, 0, 0};
	else if (obj->type == CONE)
		local_normal = normal_at_cone(local_point, obj);
	return (local_normal);
}

t_vector	normal_at_cy(t_point *point, t_shape *obj)
{
	float	dist;

	dist = (point->x * point->x) + (point->z * point->z);
	if (dist < 1 && point->y >= obj->material.max - EPSILON)
		return ((t_vector){0, 1, 0, 0});
	else if (dist < 1 && point->y <= obj->material.min + EPSILON)
		return ((t_vector){0, -1, 0, 0});
	return ((t_vector){point->x, 0, point->z, 0});
}

t_vector	normal_at_cone(t_point *point, t_shape *obj)
{
	float		dist;
	float		y;
	t_vector	normal;

	dist = (point->x * point->x) + (point->z * point->z);
	if (dist < obj->material.max * obj->material.max \
		&& point->y >= obj->material.max - EPSILON)
		return ((t_vector){0, 1, 0, 0});
	else if (dist < obj->material.min * obj->material.min \
		&& point->y <= obj->material.min + EPSILON)
		return ((t_vector){0, -1, 0, 0});
	y = sqrtf(dist);
	if (y > EPSILON)
		y = -y;
	normal = (t_vector){point->x, y, point->z, 0};
	return (normal);
}
