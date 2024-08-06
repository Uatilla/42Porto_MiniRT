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
	t_vector	point_to_ray;

	point_to_ray = subtrac_tuples(point, &data->ray.origin);
	data->ray.direction = normalize(&point_to_ray);
	obj = data->objs;
	while (obj)
	{
		ray_intersections(data, obj);
		obj = ((t_sphere *)obj)->next;
	}
	set_hit(&data->ray);
}

void	ray_intersections(t_minirt *data, void *obj)
{
	float		t[2];	
	int8_t		intersection_points;

	intersection_points = 0;
	intersection_points = ray_sphere_intersect(&data->ray, obj, t);
	if (intersection_points > 0)
	{
		if (data->ray.inter == NULL)
			one_intersection(data, intersection_points, t, obj);
		else
			more_intersections(data, intersection_points, t, obj);
	}
}

void	set_hit(t_ray *ray)
{
	if (!ray->first_hit)
		ray->first_hit = ray->inter;
	else if (ray->inter && ray->inter->hit)
	{
		if (*ray->inter->hit < *ray->first_hit->hit)
			ray->first_hit = ray->inter;
	}
}

void	one_intersection(t_minirt *data, int8_t point, float *t, t_sphere *obj)
{
	data->ray.inter = ft_calloc(sizeof(*data->ray.inter), 1);
	if (data->ray.inter == NULL)
		clear_exit(data, errno);
	data->ray.inter->count = point;
	data->ray.inter->t[0] = t[0];
	data->ray.inter->t[1] = t[1];
	if (data->ray.inter->t[0] > 0
		&& data->ray.inter->t[0] < data->ray.inter->t[1])
		data->ray.inter->hit = &data->ray.inter->t[0];
	else if (data->ray.inter->t[1] > 0)
		data->ray.inter->hit = &data->ray.inter->t[0];
	data->ray.inter->obj = obj;
}

void	more_intersections(t_minirt *data, int8_t point, float *t, t_sphere *obj)
{
	t_intersections	*temp;

	temp = ft_calloc(sizeof(*temp), 1);
	if (temp == NULL)
		clear_exit(data, errno);
	temp->count = point;
	temp->t[0] = t[0];
	temp->t[1] = t[1];
	if (data->ray.inter->t[0] > 0
		&& data->ray.inter->t[0] < data->ray.inter->t[1])
		data->ray.inter->hit = &data->ray.inter->t[0];
	else if (data->ray.inter->t[1] > 0)
		data->ray.inter->hit = &data->ray.inter->t[0];
	temp->next = data->ray.inter;
	temp->obj = obj;
	data->ray.inter = temp;
}
