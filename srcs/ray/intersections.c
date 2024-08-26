/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:12:05 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/23 19:27:25 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
*	sets the ray direction relative to the origin and point in the world
*	loop through the object list 
*		transform the ray with the inverse of the transform matrix
*	sets the first hit point if there is one
*/
void	check_intersections(t_minirt *data)
{
	t_shape	*obj;

	obj = data->world.objs;
	while (obj)
	{
		obj->trans_ray = ray_trasform(&data->ray, obj->mtx_inver);
		ray_intersections(data, obj, &obj->trans_ray);
		obj = obj->next;
	}
	first_hit(data);
	sort_intersections(&data->xs, data->inter);
}

/*
*	sees the intersection points of the ray to the object
*
*	if the ray hits the obj, will allocate a intersection struct with the
*	intersect points and the object propeties and push it to the top of the stack
*/
void	ray_intersections(t_minirt *data, t_shape *obj, t_ray *trans_ray)
{
	float		t[2];	
	int8_t		intersection_points;

	intersection_points = 0;
	if (obj->type == SP)
		intersection_points = ray_sphere_intersect(trans_ray, t);
	else if (obj->type == PL)
		intersection_points = ray_plane_intersect(trans_ray, t);
	if (intersection_points > 0)
	{
		data->xs.count += 2;
		if (data->inter == NULL)
			first_inter(data, intersection_points, t, obj);
		else
			append_inter(data, intersection_points, t, obj);
	}
}

/*
*	will update the ray->fisrt_hit pointer to the t_intersection struct if there
*	is a intersection
*/
void	first_hit(t_minirt *data)
{
	t_intersections	*temp;

	temp = data->inter;
	if (temp == NULL)
		return ;
	while (temp)
	{
		if (!data->first_hit && temp->hit > 0)
			data->first_hit = temp;
		if (temp->hit > 0 && temp->hit < data->first_hit->hit)
			data->first_hit = temp;
		temp = temp->next;
	}
}

/*
*	will allocate and set the first node of the intersections stack
*/
void	first_inter(t_minirt *data, int8_t point, float *t, t_shape *obj)
{
	data->inter = ft_calloc(sizeof(*data->inter), 1);
	if (data->inter == NULL)
		clear_exit(data, errno);
	data->inter->count = point;
	data->inter->t[0] = t[0];
	data->inter->t[1] = t[1];
	if (data->inter->t[0] > 0
		&& data->inter->t[0] < data->inter->t[1])
	{
		data->inter->hit = data->inter->t[0];
		data->inter->point = position(&data->ray, t[0]);
	}
	else if (data->inter->t[1] > 0)
	{
		data->inter->hit = data->inter->t[1];
		data->inter->point = position(&data->ray, t[1]);
	}
	data->inter->obj = obj;
}

/*
*	will allocate and set a new node to the intersection stack
*	and push it to the top
*/
void	append_inter(t_minirt *data, int8_t point, float *t, t_shape *obj)
{
	t_intersections	*temp;

	temp = ft_calloc(sizeof(*temp), 1);
	if (temp == NULL)
		clear_exit(data, errno);
	temp->count = point;
	temp->t[0] = t[0];
	temp->t[1] = t[1];
	if (temp->t[0] > 0 && temp->t[0] < temp->t[1])
	{
		temp->hit = temp->t[0];
		temp->point = position(&data->ray, t[0]);
	}
	else if (temp->t[1] > 0)
	{
		temp->hit = temp->t[1];
		temp->point = position(&data->ray, t[1]);
	}
	temp->next = data->inter;
	temp->obj = obj;
	data->inter = temp;
}
