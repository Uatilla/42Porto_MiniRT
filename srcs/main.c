/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/08 22:41:42 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


int	main(void)
{
	t_minirt 	data;
	t_light		light;
	int			y;
	int			x;
	float		world_x;
	float		world_y;
	t_vector	eye;
	t_color		color;

	t_matrix	*mtx;
	t_point		pt;
	t_point		new_pt;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);
	parse_objects(SP, &data);
	light = set_light(&(t_point){-10,10,-10,1}, &(t_color){1,1,1,999999});
	data.ray.origin = (t_point){0,0,-5,1};
	y = -1;
	while (++y < HEIGTH)
	{
		x = -1;
		while (++x < WIDTH)
		{
			world_x = map_x(x, -5, 5);
			world_y = map_y(y, -5, 5);
			check_intersections(&data, &(t_point){world_x, world_y, 5, 1});
			if (data.ray.first_hit)
			{
				light_vec(&data.ray, &light);
				color = lighting(data.ray.first_hit, &light);
				write_pixel(&data.canvas, x, y, &color);
			}
			clear_ray_inter(&data);
		}
	}

	pt = creating_point(0, 0, 1);
	mtx = mtx_create(&data, 4, 4);
	fill_idnty_mtx(mtx);
	mtx_rotation_y(mtx, 90);
	new_pt = mtx_mult_tuple(mtx, &pt);
	printf("new PT X:%f Y:%f Z:%f W:%f\n", new_pt.x, new_pt.y, new_pt.z, new_pt.w);
	clean_matrix(&data, mtx, 0);

	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
}
