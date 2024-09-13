/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:36:50 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 17:37:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
void	first_inter(t_minirt *data, float *t, t_shape *obj, t_ray *ray)
{
	data->inter = ft_calloc(sizeof(*data->inter), 1);
	if (data->inter == NULL)
		clear_exit(data, errno);
	data->inter->t[0] = t[0];
	data->inter->t[1] = t[1];
	if (data->inter->t[0] > 0
		&& data->inter->t[0] < data->inter->t[1])
	{
		data->inter->hit = data->inter->t[0];
		data->inter->point = position(ray, t[0]);
	}
	else if (data->inter->t[1] > 0)
	{
		data->inter->hit = data->inter->t[1];
		data->inter->point = position(ray, t[1]);
	}
	data->inter->obj = obj;
}

/*
*	will allocate and set a new node to the intersection stack
*	and push it to the top
*/
void	append_inter(t_minirt *data, float *t, t_shape *obj, t_ray *ray)
{
	t_intersections	*temp;

	temp = ft_calloc(sizeof(*temp), 1);
	if (temp == NULL)
		clear_exit(data, errno);
	temp->t[0] = t[0];
	temp->t[1] = t[1];
	if (temp->t[0] > 0 && temp->t[0] < temp->t[1])
	{
		temp->hit = temp->t[0];
		temp->point = position(ray, t[0]);
	}
	else if (temp->t[1] > 0)
	{
		temp->hit = temp->t[1];
		temp->point = position(ray, t[1]);
	}
	temp->next = data->inter;
	temp->obj = obj;
	data->inter = temp;
}

// add a intersection struct to the stack of intersections
void	add_intersection(t_minirt *data, float *t, t_shape *obj, t_ray *ray)
{
	if (data->inter == NULL)
		first_inter(data, t, obj, ray);
	else
		append_inter(data, t, obj, ray);
}
