/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tuples.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:21:50 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 19:19:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

	/// @brief Change vector lenght.
	/// @param a Tuple a to be multiplied.
	/// @param b Tuple b to be multiplied.
	/// @return Lenght of the new vector.
float	dot_product(t_tuple *a, t_tuple *b)
{
	t_tuple	res;

	res.x = a->x * b->x;
	res.y = a->y * b->y;
	res.z = a->z * b->z;
	if (a->w != 999999)
		res.w = a->w * b->w;
	else
		res.w = 999999;
	return (res.x + res.y + res.z + res.w);
}

	/// @brief Find the lenght of the vector.
	/// @param a Tuple a to the lenght to be found.
	/// @return Lenght of the vector.
float	magnitude(t_tuple *a)
{
	t_tuple	res;

	res.x = a->x * a->x;
	res.y = a->y * a->y;
	res.z = a->z * a->z;
	if (a->w != 999999)
		res.w = a->w * a->w;
	else
		res.w = 999999;
	return (sqrtf(res.x + res.y + res.z + res.w));
}

	/// @brief Convert a vector into an unit vector.
	/// @param a Vector to be normalized.
	/// @return Vector normalized.
t_tuple	normalize(t_tuple *a)
{
	return (creating_tuple(a->x / magnitude(a), a->y / magnitude(a), \
			a->z / magnitude(a), a->w / magnitude(a)));
}

	/// @brief Find a new vector when an intersection happens.
	/// @param a First vector.
	/// @param b Second vector.
	/// @return Vector found.
t_tuple	cross_product(t_tuple *a, t_tuple *b)
{
	return (creating_tuple((a->y * b->z) - (a->z * b->y), \
			(a->z * b->x) - (a->x * b->z), \
			(a->x * b->y) - (a->y * b->x), 0));
}

t_color	color_multiply(t_color *c1, t_color *c2)
{
	return ((t_color){{c1->r * c2->r,
			c1->g * c2->g,
			c1->b * c2->b,
			c1->w * c2->w}});
}
