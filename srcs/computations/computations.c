/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:00:57 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 17:28:08 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 *	this function prepare computation that will be utilized by shade_hit
 *
 */
t_comps	prepare_computations(t_intersections *i, t_ray *ray, t_minirt *data)
{
	t_comps	comps;
	t_point	over_point;

	comps.t = i->hit;
	comps.obj = i->obj;
	comps.point = i->point;
	comps.eyev = negating_tuple(&ray->direction);
	comps.normalv = normal_at(comps.obj, &comps.point, data);
	if (dot_product(&comps.normalv, &comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negating_tuple(&comps.normalv);
	}
	else
		comps.inside = false;
	if (comps.obj->type == CONE)
		comps.over_point = mult_tuple_scalar(&comps.normalv, EPSILON * 600000);
	else
		comps.over_point = mult_tuple_scalar(&comps.normalv, EPSILON * 400);
	comps.over_point = sum_tuples(&comps.point, &comps.over_point);
	comps.reflectv = reflect(&ray->direction, &comps.normalv);
	return (comps);
}

/*
 * returs true or false, if the point p is showdown of not
 *
 * this is done by casting a ray from the point to the light origim and checks
 * if intercects a object or not
*/
bool	is_shadowed(t_world *w, t_light *light, t_point *p)
{
	t_minirt	data;
	t_vector	v;
	float		distance;
	t_ray		ray;

	ft_memset(&data, 0, sizeof(data));
	data.world = *w;
	v = subtrac_tuples(&light->position, p);
	distance = magnitude(&v);
	ray.direction = normalize(&v);
	ray.origin = *p;
	intersections(&data, &ray);
	if (data.first_hit && distance > data.first_hit->hit)
	{
		clear_ray_inter(&data);
		return (true);
	}
	clear_ray_inter(&data);
	return (false);
}

/*
*	if the objects material has a reflective component, then we check if the 
*	reflected_ray intersects a object, if it does we return the color of that
*	object multiplied by the reflective component.
*
*	Then will add the reflected_color with the object efective color.
*
*	The remaining parameter is the end the recursive call if we have two
*	reflective objects pointing at each other
*/
t_color	reflected_color(t_comps *comps, t_minirt *data, int8_t remaining)
{
	t_color	color;
	t_ray	reflected_ray;

	if (comps->obj->material.reflective == 0 || remaining == 0)
		return ((t_color){0, 0, 0, 999999});
	reflected_ray.origin = comps->over_point;
	reflected_ray.direction = comps->reflectv;
	color = color_at(data, &reflected_ray, remaining - 1);
	color = mult_tuple_scalar(&color, comps->obj->material.reflective);
	return (color);
}
