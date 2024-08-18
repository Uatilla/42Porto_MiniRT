/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/19 00:08:01 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(void)
{
	t_minirt	data;
	t_light		light;
	t_color		color;
	int			x;
	int			y;

	ft_memset(&data, 0, sizeof(data));
	parse_objects(SP, &data);
	mtx_scaling(((t_sphere *)data.objs)->mtx_trans, &(t_tuple){2, 2, 2, 1});
	((t_sphere *)data.objs)->mtx_inver = mtx_inverse(&data, ((t_sphere *)data.objs)->mtx_trans);
	data.camera = camera_construct(HEIGTH, WIDTH, PI / 2);
	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 1});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);
	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 69});
	start_mlx(&data.canvas);

	y = -1;
	while (++y < HEIGTH)
	{
		x = -1;
		while (++x < WIDTH)
		{
			data.ray = ray_for_pixel(&data.camera, x, y);
			check_intersections(&data);
			if (data.first_hit)
			{
				light_vec(&((t_sphere *)data.first_hit->obj)->trans_ray, &light, &data);
				color = lighting(data.first_hit, &light);
				write_pixel(&data.canvas, x, y, &color);
			}
			clear_ray_inter(&data);
		}
	}
	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	printf("end\n");
	mlx_loop(data.canvas.mlx);
}
