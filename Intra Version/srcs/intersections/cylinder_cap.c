/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:36:54 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 19:37:18 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	check_cy_range(t_ray *ray, float t, t_shape *obj)
{
	float	y;
	float	cap_t;

	y = ray->origin.y + (ray->direction.y * t);
	if (obj->material.min < y && y < obj->material.max)
		return (true);
	return (false);
}

bool	check_cap(t_ray *ray, float t, t_shape *obj, int8_t	order)
{
	float	x;
	float	z;

	x = ray->origin.x + (t * ray->direction.x);
	z = ray->origin.z + (t * ray->direction.z);
	if (obj->type == CY)
		return (((x * x) + (z * z)) <= 1);
	else if (obj->type == CONE)
	{
		if (order == 1)
			return (((x * x) + (z * z)) <= fabs(obj->material.min \
				* obj->material.min));
		else if (order == 2)
			return (((x * x) + (z * z)) <= fabs(obj->material.max \
				* obj->material.max));
	}
	return (false);
}

int8_t	ray_cap_inter(t_ray *ray, float *t, t_shape *obj)
{
	bool	count[2];

	if (obj->material.closed == false || fabs(ray->direction.y) < EPSILON)
		return (0);
	t[0] = (obj->material.min - ray->origin.y) / ray->direction.y;
	t[1] = (obj->material.max - ray->origin.y) / ray->direction.y;
	count[0] = check_cap(ray, t[0], obj, 1);
	count[1] = check_cap(ray, t[1], obj, 2);
	return (intercections_count(count, t));
}
