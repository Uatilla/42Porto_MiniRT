/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:04:30 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/07 21:06:28 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_objects(enum e_identifyer type, t_minirt *data)
{
	if (type == SP)
		parse_sphere(data);
}

/*
*	adds a object node to the top of the objcts stack
*	creats a stack if is empty
*/
void	parse_sphere(t_minirt *data)
{
	t_sphere	*sphere;

	if (data->objs == NULL)
	{
		data->objs = ft_calloc(sizeof(t_sphere), 1);
		if (data->objs == NULL)
			clear_exit(data, errno);
		((t_sphere *)data->objs)->center = (t_tuple){0, 0, 0, 1};
		((t_sphere *)data->objs)->type = SP;
		((t_sphere *)data->objs)->diameter = 2;
		set_materials(&((t_sphere *)data->objs)->material);
		return ;
	}
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (sphere == NULL)
		clear_exit(data, errno);
	sphere->center = (t_tuple){0, 0, 0, 1};
	sphere->type = SP;
	sphere->diameter = 2;
	set_materials(&sphere->material);
	sphere->next = data->objs;
	data->objs = sphere;
}

/*
*	fisrst inplementation
*/
void	set_materials(t_material *material)
{
	material->color = (t_color){1, 0.2, 0.8, 999999};
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 100.0;
}
