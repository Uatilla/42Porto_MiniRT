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

void	check_intersections(t_minirt *data, t_point *point)
{
	void	*obj;

	obj = data->objs;
	while (obj)
	{
		ray_intersections(&data->ray, obj, point);
		obj = ((t_sphere *)obj)->next;
	}
}

void	ray_intersections(t_ray *ray, void *obj, t_point *point)
{
	float		t[2];	
	t_vector	point_to_ray;
	int8_t		intersection_points;

	intersection_points = 0;
	point_to_ray = subtrac_tuples(point, &ray->origin);
	ray->direction = normalize(&point_to_ray);
	intersection_points = ray_sphere_intersect(ray, obj, t);
	if (intersection_points > 0)
	{
		if (ray->inter == NULL)
		{
			ray->inter = ft_calloc(sizeof(*ray->inter), 1);
			ray->inter->count = intersection_points;
			ray->inter->t[0] = t[0];
			ray->inter->t[1] = t[1];
			ray->inter->obj = obj;
		}
		else
		{
			t_intersections	*temp;

			temp = ft_calloc(sizeof(*temp), 1);
			temp->count = intersection_points;
			temp->t[0] = t[0];
			temp->t[1] = t[1];
			temp->next = ray->inter;
			temp->obj = obj;
			ray->inter = temp;
		}
		if (ray->hit == NULL)
		{
			if (ray->inter->t[0] > 0)
				ray->hit = &ray->inter->t[0];
		}
		else
		{
			if (ray->inter->t[0] > 0 && *ray->hit > ray->inter->t[0])
				ray->hit = &ray->inter->t[0];
		}
	}
}

void	one_intersection(t_minirt *data)
{
	return ;
}
