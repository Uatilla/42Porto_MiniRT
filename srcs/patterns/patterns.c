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
	if (fmod(point->x, 2) == 0)
		return (patterns->a);
	else
		return (patterns->b);
}
