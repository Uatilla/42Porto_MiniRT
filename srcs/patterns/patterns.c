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

// calls the apropriate patterns function for the obj
t_color	pattern_at(t_pattern *p, t_point *point, t_shape *obj, enum e_p type)
{
	t_point	object_point;
	t_point patterns_point;

	object_point = mtx_mult_tuple(obj->mtx_inver, point);
	patterns_point = mtx_mult_tuple(p->inver, &object_point);
	if (type == STR)
		return (stripe_at(p, &patterns_point));
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
