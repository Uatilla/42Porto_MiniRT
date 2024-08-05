/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:04:30 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/05 22:09:26 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_objects(enum e_identifyer type, t_minirt *data)
{
	if (type == SP)
		parse_sphere(data);
}

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
		return ;
	}
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (sphere == NULL)
		clear_exit(data, errno);
	sphere->center = (t_tuple){0, 0, 0, 1};
	sphere->type = SP;
	sphere->diameter = 2;
	sphere->next = data->objs;
	data->objs = sphere;
}