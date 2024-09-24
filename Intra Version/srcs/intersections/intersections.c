/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:33:53 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 19:40:06 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
*	sets the ray direction relative to the origin and point in the world
*	loop through the object list 
*		transform the ray with the inverse of the transform matrix
*	sets the first hit point if there is one
*/
void	intersections(t_minirt *data, t_ray *ray)
{
	t_shape	*obj;

	obj = data->world.objs;
	while (obj)
	{
		obj->trans_ray = ray_trasform(ray, obj->mtx_inver);
		ray_intersections(data, obj, &obj->trans_ray, ray);
		obj = obj->next;
	}
	first_hit(data);
}

/*
*	sees the intersection points of the ray to the object
*
*	if the ray hits the obj, will allocate a intersection struct with the
*	intersect points and the object propeties and push it to the top of the stack
*/
void	ray_intersections(t_minirt *data, t_shape *obj, t_ray *trans_ray, \
		t_ray *ray)
{
	float		t[2];	
	int8_t		intersection_points;

	intersection_points = 0;
	if (obj->type == SP)
		intersection_points = ray_sphere_intersect(trans_ray, t);
	else if (obj->type == PL)
		intersection_points = ray_plane_intersect(trans_ray, t);
	else if (obj->type == CY)
	{
		intersection_points = ray_cap_inter(trans_ray, t, obj);
		if (intersection_points > 0)
			add_intersection(data, t, obj, ray);
		intersection_points = ray_cylinder_intersect(trans_ray, t, obj);
	}
	else if (obj->type == CONE)
	{
		intersection_points = ray_cap_inter(trans_ray, t, obj);
		if (intersection_points > 0)
			add_intersection(data, t, obj, ray);
		intersection_points = ray_cone_intersect(trans_ray, t, obj);
	}
	if (intersection_points > 0)
		add_intersection(data, t, obj, ray);
}
