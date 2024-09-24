/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:47:41 by uviana-a          #+#    #+#             */
/*   Updated: 2024/09/20 22:47:43 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	ring_patt(t_pattern *pattern, t_point *point)
{
	t_color	c;

	if ((int)sqrtf((point->x * point->x) + (point->z * point->z)) % 2 == 0)
		c = pattern->a;
	else
		c = pattern->b;
	return (c);
}

// checker pattern
t_color	checker_patt(t_pattern *pattern, t_point *point)
{
	t_color	c;

	if ((int)(floor(point->x) + floor(point->y) + floor(point->z)) % 2 == 0)
		c = pattern->a;
	else
		c = pattern->b;
	return (c);
}

// calls the apropriate patterns function for the obj
t_color	pattern_at(t_pattern *p, t_point *point, t_shape *obj, enum e_p type)
{
	t_point	object_point;
	t_point	patterns_point;

	object_point = mtx_mult_tuple(obj->mtx_inver, point);
	patterns_point = mtx_mult_tuple(p->inver, &object_point);
	if (type == STR)
		return (stripe_at(p, &patterns_point));
	else if (type == PC)
		return (point_color(&patterns_point));
	else if (type == GR)
		return (gradient(p, &patterns_point));
	else if (type == RNG)
		return (ring_patt(p, &patterns_point));
	else if (type == CHK)
		return (checker_patt(p, &patterns_point));
	return ((t_color){0, 0, 0, 0});
}

// sets the collor of the obj at a given point if te obj has a pattern
void	set_pattern(t_intersections *inter, t_point *point)
{
	if (inter->obj->material.pattern.has)
	{
		inter->obj->material.color = pattern_at(&inter->obj->material.pattern, \
			point, inter->obj, inter->obj->material.pattern.type);
	}
}
