/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:53:56 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/29 17:16:08 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// sets the pattern for the object
t_pattern	stripe_pattern(t_color *a, t_color *b, enum e_p type)
{
	t_pattern stripe;

	stripe.trans = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(stripe.trans);
	stripe.a = *a;
	stripe.b = *b;
	stripe.has = true;
	stripe.type = type;
	return (stripe);
}

// return the collor at at given point for a stripe patterns
t_color	stripe_at(t_pattern *patterns, t_point *point)
{
	t_color	c;

	if ((int)point->x % 2 == 0)
		c = patterns->a;
	else
		c = patterns->b;
	return (c);
}

// directly translate the point x/y/x to color r/g/b
t_color	point_color(t_point *point)
{
	return ((t_color){point->x, point->y, point->z, point->w});
}

// sets the gradient between collor a and collor b from pattern
t_color	gradient(t_pattern *pattern, t_point *point)
{
	t_color	distance;
	float	fraction;
	t_color	ret;

	distance = subtrac_tuples(&pattern->a, &pattern->b);
	fraction = point->x;
	ret = mult_tuple_scalar(&distance, fraction);
	return (sum_tuples(&pattern->a, &ret));
}

// calls the apropriate patterns function for the obj
t_color	pattern_at(t_pattern *p, t_point *point, t_shape *obj, enum e_p type)
{
	t_point	object_point;
	t_point patterns_point;

	object_point = mtx_mult_tuple(obj->mtx_inver, point);
	patterns_point = mtx_mult_tuple(p->inver, &object_point);
	if (type == STR)
		return (stripe_at(p, &patterns_point));
	else if (type == PC)
		return (point_color(&patterns_point));
	else if (type == GR)
		return (gradient(p, &patterns_point));
	return ((t_color){0, 0, 0, 0});
}

// sets the collor of the obj at a given point if te obj has a pattern
void	set_pattern(t_intersections *inter)
{
		if (inter->obj->material.pattern.has)
		{
			inter->obj->material.color =
			pattern_at(&inter->obj->material.pattern,
		   	&inter->point, inter->obj, inter->obj->material.pattern.type);
		}
}
