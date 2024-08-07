/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:12:05 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/07 18:47:15 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
*	sets the ray direction relative to the origin and point in the world
*	loop through the object list and see if the ray intersects each one
*	sets the first hit point if there is one
*/
void	check_intersections(t_minirt *data, t_point *point)
{
	t_vector	point_to_ray;
	void		*obj;

	point_to_ray = subtrac_tuples(point, &data->ray.origin);
	data->ray.direction = normalize(&point_to_ray);
	obj = data->objs;
	while (obj)
	{
		ray_intersections(data, obj);
		obj = ((t_sphere *)obj)->next;
	}
	first_hit(&data->ray);
}

/*
*	sees the intersection points of the ray to the object
*
*	if the ray hits the obj, will allocate a intersection struct with the
*	intersect points and the object propeties and push it to the top of the stack
*/
void	ray_intersections(t_minirt *data, void *obj)
{
	float		t[2];	
	int8_t		intersection_points;

	intersection_points = 0;
	intersection_points = ray_sphere_intersect(&data->ray, obj, t);
	if (intersection_points > 0)
	{
		if (data->ray.inter == NULL)
			first_inter(data, intersection_points, t, obj);
		else
			append_inter(data, intersection_points, t, obj);
	}
}

/*
*	will update the ray->fisrt_hit pointer to the t_intersection struct if there
*	is a intersection
*/
void	first_hit(t_ray *ray)
{
	if (!ray->first_hit)
		ray->first_hit = ray->inter;
	else if (ray->inter && ray->inter->hit)
	{
		if (ray->inter->hit < ray->first_hit->hit)
			ray->first_hit = ray->inter;
	}
}

/*
*	will allocate and set the first node of the intersections stack
*/
void	first_inter(t_minirt *data, int8_t point, float *t, t_sphere *obj)
{
	data->ray.inter = ft_calloc(sizeof(*data->ray.inter), 1);
	if (data->ray.inter == NULL)
		clear_exit(data, errno);
	data->ray.inter->count = point;
	data->ray.inter->t[0] = t[0];
	data->ray.inter->t[1] = t[1];
	if (data->ray.inter->t[0] > 0
		&& data->ray.inter->t[0] < data->ray.inter->t[1])
		data->ray.inter->hit = data->ray.inter->t[0];
	else if (data->ray.inter->t[1] > 0)
		data->ray.inter->hit = data->ray.inter->t[1];
	data->ray.inter->obj = obj;
}

/*
*	will allocate and set a new node to the intersection stack
*	and push it to the top
*/
void	append_inter(t_minirt *data, int8_t point, float *t, t_sphere *obj)
{
	t_intersections	*temp;

	temp = ft_calloc(sizeof(*temp), 1);
	if (temp == NULL)
		clear_exit(data, errno);
	temp->count = point;
	temp->t[0] = t[0];
	temp->t[1] = t[1];
	if (temp->t[0] > 0 && temp->t[0] < temp->t[1])
		temp->hit = temp->t[0];
	else if (temp->t[1] > 0)
		temp->hit = temp->t[1];
	temp->next = data->ray.inter;
	temp->obj = obj;
	data->ray.inter = temp;
}
