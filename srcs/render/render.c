/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:23:02 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/22 15:25:07 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	render(t_minirt *data)
{
	int			x;
	int			y;
	t_color		color;

	y = -1;
	while (++y < data->camera.vsize - 1)
	{
		x = -1;
		while (++x < data->camera.hsize - 1)
		{
			data->ray = ray_for_pixel(&data->camera, x, y);
			color = color_at(data);
			write_pixel(&data->canvas, x, y, &color);
		}
	}
	ft_printf("end render\n");
	manage_interface(data);
}
