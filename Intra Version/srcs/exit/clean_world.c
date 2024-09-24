/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:30:43 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/19 17:00:30 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	clean_world(t_world *world)
{
	if (world->objs)
		clean_sphere(world->objs);
	if (world->light)
		clean_light(world->light);
}

void	clean_light(t_light *light)
{
	t_light	*ptr;

	ptr = light;
	while (light)
	{
		ptr = ptr->next;
		free(light);
		light = ptr;
	}
}

void	clean_sphere(t_sphere *sp)
{
	t_sphere	*ptr;

	ptr = sp;
	while (sp)
	{
		if (ptr->mtx_trans)
			clean_matrix(NULL, ptr->mtx_trans, 0);
		if (ptr->mtx_inver)
			clean_matrix(NULL, ptr->mtx_inver, 0);
		if (ptr->material.pattern.has)
		{
			clean_matrix(NULL, ptr->material.pattern.trans, 0);
			clean_matrix(NULL, ptr->material.pattern.inver, 0);
		}
		ptr = ptr->next;
		free(sp);
		sp = ptr;
	}
}
