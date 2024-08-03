/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:27:44 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/03 19:19:30 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	discriminant(t_ray *ray, t_sphere *sphere)
{
	float	a;
	float	b;
	float	c;

	a = dot_product(&ray->direction, &ray->direction);
	b = 2 * dot_put

}
