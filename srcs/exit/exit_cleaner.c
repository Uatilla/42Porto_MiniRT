/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:30:03 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/05 22:06:12 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void    clear_exit(t_minirt *mrt, int status)
{
    if (!mrt)
        exit(EXIT_FAILURE);
    printf("OUT_STATUS\n");
	clear_objs(mrt->objs);
    exit(status);
}

void    ft_error(char *msg)
{
    ft_putstr_fd(msg, 2);
}

void	clear_objs(void	*objs)
{
	void	*ptr;

	ptr = objs;
	while (objs)
	{
		if (((t_sphere *)objs)->type == SP)
		{
			objs = ((t_sphere *)objs)->next;
			free(ptr);
			ptr = objs;
		}
	}
}

void	clear_ray_inter(t_minirt *data)
{
	t_intersections *ptr;

	ptr = data->ray.inter;
	while (ptr)
	{
		ptr = ptr->next;
		free(data->ray.inter);
		data->ray.inter = ptr;
	}
	data->ray.first_hit = NULL;
}
