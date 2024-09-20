/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:53:56 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 17:31:01 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// sets the pattern for the object
t_pattern	stripe_pattern(t_color *a, t_color *b, enum e_p type)
{
	t_pattern	stripe;

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
	fraction = point->x - floor(point->x);
	ret = mult_tuple_scalar(&distance, fraction);
	return (sum_tuples(&pattern->a, &ret));
}
