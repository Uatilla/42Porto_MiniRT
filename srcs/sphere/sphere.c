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

/*
 * finds the intersections points from the ray to the sphere
 * store them at t[0] and t[1] and return the number of intersection
 * if the determinant is < 0 there is no intersection and returns 0
 * if t[0] == t[1] there is only one point and return 1
 * if the determinat is > 0 there is two points and returns 2
*/
int8_t	intersect(t_ray *ray, t_sphere *sphere, float *t)
{
	float	a;
	float	b;
	float	c;
	t_tuple	sphere_to_ray;
	float	discriminant;

	if (!ray || !sphere || !t)
		return (0);
	sphere_to_ray = subtrac_tuples(&ray->origin, &sphere->center);
	a = dot_product(&ray->direction, &ray->direction);
	b = 2 * dot_product(&ray->direction, &sphere_to_ray);
	c = dot_product(&sphere_to_ray, &sphere_to_ray)
		- (sphere->radius * sphere->radius);
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t[0] = (-b - sqrtf(discriminant)) / (2 * a);
	t[1] = (-b + sqrtf(discriminant)) / (2 * a);
	if (t[0] == t[1])
		return (1);
	return (2);
}

/*
 * takes a linked list of intersections and adds a new one at the end of it
*/
void	intersections(t_intersections **head, t_inter *new_inter)
{
	static t_intersections	*tail;

	if (!(*head))
	{
		(*head) = ft_calloc(sizeof(**head), 1);
		(*head)->node = ft_calloc(sizeof(*new_inter), 1);
		if ((*head)->node == NULL)
			exit(errno);
		ft_memmove((*head)->node, new_inter, sizeof(*new_inter));
		tail = *head;
		return ;
	}
	tail->next = ft_calloc(sizeof(**head), 1);
	tail->next->node = ft_calloc(sizeof(*new_inter), 1);
	if (tail->next->node == NULL)
		exit(errno);
	tail = tail->next;
	ft_memmove(tail->node, new_inter, sizeof(*new_inter));
}
