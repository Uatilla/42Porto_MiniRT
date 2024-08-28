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

	y = -1;
	while (++y < data->camera.vsize - 1)
	{
		x = -1;
		while (++x < data->camera.hsize - 1)
		{
			data->ray = ray_for_pixel(&data->camera, x, y);
			color_at(data, x, y);
		}
	}
	ft_printf("end render\n");

	
	clean_world(&data->world);
	clean_matrix(data, data->camera.trans, 0);
	clean_matrix(data, data->camera.inver, 0);


	//mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	//mlx_key_hook(data.canvas.win, &handle_key_event, &data);

	mlx_put_image_to_window(data->canvas.mlx, data->canvas.win, data->canvas.img, 0, 0);
	//mlx_hook(data->canvas.win, KeyPress, KeyPressMask, handle_key_event, data);
	mlx_hook(data->canvas.win, 17, 0L, close_window, data);
	mlx_key_hook(data->canvas.win, &handle_key_event, data);
	mlx_loop(data->canvas.mlx);
}
