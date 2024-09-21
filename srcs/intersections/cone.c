/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:39:05 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 19:39:30 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int8_t	ray_cone_intersect(t_ray *ray, float *t, t_shape *obj)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	bool	count[2];

	set_cone_intersect(&a, &b, &c, ray);
	if (a == 0 && b == 0)
		return (0);
	if (a == 0)
	{
		t[0] = -c / 2 * b;
		t[1] = -c / 2 * b;
		return (1);
	}
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

void	set_cone_intersect(float *a, float *b, float *c, t_ray *ray)
{
	*a = (ray->direction.x * ray->direction.x) - (ray->direction.y
			* ray->direction.y) + (ray->direction.z * ray->direction.z);
	*b = (2 * ray->origin.x * ray->direction.x) - (2 * ray->origin.y
			* ray->direction.y) + (2 * ray->origin.z * ray->direction.z);
	*c = (ray->origin.x * ray->origin.x) - (ray->origin.y
			* ray->origin.y) + (ray->origin.z * ray->origin.z);
}
