/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/19 17:12:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render(t_minirt *data);

int	main(void)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);
	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);

	parse_sphere(&data.world);
	mtx_scaling(data.world.sphere->mtx_trans, &(t_point){10, 0.01, 10, 1});
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);

	data.camera = camera_construct(WIDTH, HEIGTH, PI / 2);
	clean_matrix(&data, data.camera.trans, 0);
	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);

	render(&data);
	clean_matrix(&data, data.camera.trans, 0);
	clean_matrix(&data, data.camera.inver, 0);
	clean_world(&data.world);
	return (0);
}

void	render(t_minirt *data)
{
	int			x;
	int			y;

	y = -1;
	while (++y < data->camera.hsize - 1)
	{
		x = -1;
		while (++x < data->camera.vsize - 1)
		{
			data->ray = ray_for_pixel(&data->camera, x, y);
			color_at(data, x, y);
		}
	}
	printf("end render\n");
	mlx_put_image_to_window(data->canvas.mlx, data->canvas.win, data->canvas.img, 0, 0);
	mlx_loop(data->canvas.mlx);
}
