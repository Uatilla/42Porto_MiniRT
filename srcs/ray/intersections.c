/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:12:05 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/05 18:31:08 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ray_inter(t_ray *ray, t_sphere *obj, t_point *point)
{
	float	t[2];	
	int8_t	count;
	t_vector point_to_ray;

	point_to_ray = subtrac_tuples(point, &ray->origin);
	ray->direction = normalize(&point_to_ray);
	count = ray_sphere_intersect(ray, obj, t);
	if (count > 0)
	{
		if (ray->inter == NULL)
		{
			ray->inter = ft_calloc(sizeof(&ray->inter), 1);
			ray->inter->count = count;
			ray->inter->t[0] = t[0];
			ray->inter->t[1] = t[1];
			ray->inter->obj = SP;
		}
		else
		{
			t_intersections	*temp;

			temp = ft_calloc(sizeof(*temp), 1);
			temp->count = count;
			temp->t[0] = t[0];
			temp->t[1] = t[1];
			temp->obj = SP;
			temp->next = ray->inter;
			ray->inter = temp;
		}
		if (ray->hit == NULL)
		{
			if (ray->inter->t[0] > 0)
				ray->hit = &ray->inter->t[0];
		}
	}
}
