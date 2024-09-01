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

t_pattern stripe_pattern(t_color *a, t_color *b)
{
	t_pattern stripe;

	stripe.trans = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(stripe.trans);
	stripe.a = *a;
	stripe.b = *b;
	stripe.has = true;
	return (stripe);
}

t_color	stripe_at(t_pattern *patterns, t_point *point)
{
	t_color	c;

	if ((int)point->x % 2 == 0)
		c = patterns->a;
	else
		c = patterns->b;
	return (c);
}

t_color	stripe_at_obj(t_pattern *patterns, t_point *point, t_shape *obj)
{
	t_point	object_point;
	t_point patterns_point;

	object_point = mtx_mult_tuple(obj->mtx_inver, point);
	patterns_point = mtx_mult_tuple(patterns->inver, &object_point);
	return (stripe_at(patterns, &patterns_point));
}

void	set_stripe_pattern(t_intersections *inter)
{
		if (inter->obj->material.pattern.has)
		{
			inter->obj->material.color =
			stripe_at_obj(&inter->obj->material.pattern,
				 &inter->point, inter->obj);
		}
}
