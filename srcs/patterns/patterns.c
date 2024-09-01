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

void	set_stripe_pattern(t_intersections *inter)
{
		if (inter->obj->material.pattern.has)
		{
			inter->obj->material.color =
			stripe_at(&inter->obj->material.pattern, &inter->point);
		}
}
