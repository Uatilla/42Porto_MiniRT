/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:01:20 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 19:40:00 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int8_t	ray_plane_intersect(t_ray *ray, float *t)
{
	if (fabs(ray->direction.y) < EPSILON)
		return (0);
	t[0] = -ray->origin.y / ray->direction.y;
	t[1] = -ray->origin.y / ray->direction.y;
	return (1);
}
