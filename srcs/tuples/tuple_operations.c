/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:05:22 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/02 21:49:09 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_tuple	tuple_add(t_tuple *a, t_tuple *b)
{
	t_tuple	ret;

	ret.x = a->x + b->x;
	ret.y = a->y + b->y;
	ret.z = a->z + b->z;
	ret.w = a->w + b->w;
	return (ret);
}
