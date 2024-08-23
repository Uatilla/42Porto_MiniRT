/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:01:20 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int8_t ray_plane_intersect(t_ray *ray, float *t)
{
	float ray_dir;

	ray_dir = ray->direction.y;
	if (fabsf(ray->direction.y) < EPSILON) //|| compare_float(0.0, ray->direction.y))
		return (0);
	t[0] = -ray->origin.y / ray->direction.y;
	t[1] = -ray->origin.y / ray->direction.y;
	return (1);
}
