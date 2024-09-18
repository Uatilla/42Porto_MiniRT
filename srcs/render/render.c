/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:23:02 by Jburlama          #+#    #+#             */
/*   Updated: 2024/09/13 17:31:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	render(t_minirt *data)
{
	t_color		color;
	t_ray		ray;
	int			x;
	int			y;

	y = -1;
	while (++y < data->camera.vsize - 1)
	{
		x = -1;
		while (++x < data->camera.hsize - 1)
		{
			ray = ray_for_pixel(&data->camera, x, y);
			color = color_at(data, &ray, 5);
			write_pixel(&data->canvas, x, y, &color);
		}
	}
	printf("RENDER\t\t[OK]\n");
	manage_interface(data);
}
