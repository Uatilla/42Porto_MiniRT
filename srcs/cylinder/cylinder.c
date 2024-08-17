/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:37:04 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/10 21:49:38 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minirt.h"

// sets the t values for the ray cylinder intersections
// returns 0 if no intersections
// returns 1 if only one intersection
// returns 2 if tow intersections
//
// The algorithm derivates from the formula
// vetorial V(t) = O + Dt com a do circulo x^2 + z^2 = r^2 (asumindo que o 
// cylindro tem altura infinita no eixo y e raio 1)
//
// (Ox + Dxt)^2 + (Oz + Dzt)^2 = 1
int8_t	ray_cylinder_intersect(t_ray *ray, float *t)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;

	a = (ray->direction.x * ray->direction.x) +
		(ray->direction.z * ray->direction.z);
	if (a < 0)
		return (0);
	b = (2 * ray->origin.x * ray->direction.x) +
		(2 * ray->origin.z * ray->direction.z);
	c = (ray->origin.x * ray->origin.x) + (ray->origin.z * ray->origin.z) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t[0] = (-b - sqrtf(discriminant)) / (2 * a);
	t[1] = (-b + sqrtf(discriminant)) / (2 * a);
	if (t[0] == t[1])
		return (1);
	return (2);
}
