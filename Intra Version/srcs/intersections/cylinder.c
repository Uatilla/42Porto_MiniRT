/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:37:04 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 19:39:16 by Jburlama         ###   ########.fr       */
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
int8_t	ray_cylinder_intersect(t_ray *ray, float *t, t_shape *obj)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	bool	count[2];

	a = (ray->direction.x * ray->direction.x) + (ray->direction.z
			* ray->direction.z);
	if (fabs(a) < EPSILON)
		return (0);
	b = (2 * ray->origin.x * ray->direction.x) + (2 * ray->origin.z
			* ray->direction.z);
	c = (ray->origin.x * ray->origin.x) + (ray->origin.z
			* ray->origin.z) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	if (t[0] > t[1])
		swap(t);
	count[0] = check_cy_range(ray, t[0], obj);
	count[1] = check_cy_range(ray, t[1], obj);
	return (intercections_count(count, t));
}

int8_t	intercections_count(bool *count, float *t)
{
	if (count[0] && count[1])
	{
		if (t[0] == t[1])
			return (1);
		else
			return (2);
	}
	else if (!count[0] && !count[1])
		return (0);
	else if (count[0])
	{
		t[1] = t[0];
		return (1);
	}
	else if (count[1])
	{
		t[0] = t[1];
		return (1);
	}
	return (0);
}

void	swap(float *t)
{
	float	temp;

	temp = t[0];
	t[0] = t[1];
	t[1] = temp;
}
