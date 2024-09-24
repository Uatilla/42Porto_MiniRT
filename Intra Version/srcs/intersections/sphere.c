/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:27:44 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/23 19:25:07 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
 * finds the intersections points from the ray to the sphere
 * store them at t[0] and t[1] and return the number of intersection
 * if the determinant is < 0 there is no intersection and returns 0
 * if t[0] == t[1] there is only one point and return 1
 * if the determinat is > 0 there is two points and returns 2
*/
int8_t	ray_sphere_intersect(t_ray *ray, float *t)
{
	float	a;
	float	b;
	float	c;
	t_tuple	sphere_to_ray;
	float	discriminant;

	if (!ray || !t)
		return (0);
	sphere_to_ray = subtrac_tuples(&ray->origin, &(t_point){0, 0, 0, 1});
	a = dot_product(&ray->direction, &ray->direction);
	b = 2 * dot_product(&ray->direction, &ray->origin);
	c = dot_product(&sphere_to_ray, &sphere_to_ray) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t[0] = (-b - sqrtf(discriminant)) / (2 * a);
	t[1] = (-b + sqrtf(discriminant)) / (2 * a);
	if (t[0] == t[1])
		return (1);
	return (2);
}
