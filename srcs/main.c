/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/05 22:09:47 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	clear_objs(void	*objs);

int main(void)
{
	t_minirt	data;


	ft_memset(&data, 0, sizeof(data));
	int		i = 1;
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	parse_objects(SP, &data);
	void	*temp = data.objs;
	while (temp != NULL)
	{
		if (((t_sphere *)data.objs)->type == SP)
	  	{
			t_sphere	*ptr = (t_sphere *)temp;
			printf("----------------objs %i---------------\n", i);
			printf("type %i\n", ptr->type);
			printf("center %f %f %f %f\n", ptr->center.x, ptr->center.y, ptr->center.z, ptr->center.w);
			printf("diameter %f\n", ptr->diameter);
			printf("next %p\n", ptr->next);
			temp = ((t_sphere *)temp)->next;
		}
		i++;
	}
	clear_objs(data.objs);
    return (0);
}
