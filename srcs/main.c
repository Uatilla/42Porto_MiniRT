/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/10 21:49:33 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// nao esquecer de chamar ft_memeset para data;
// nao esquecer de setar a origem do ray e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
// comecar com start_mlx, e nao esquecer de chamar no fim:
// 		mlx_put_image_to_window e mlx_loop
int	main(void)
{
	t_minirt	data;
	t_light		light;
	t_color		color;
	int			x;
	int			y;
	float		w_x;
	float		w_y;


	ft_memset(&data, 0, sizeof(data));
	parse_objects(SP, &data);
	mtx_scaling(((t_sphere *)data.objs)->mtx_trans, &(t_tuple){0.5, 0.5, 0.5, 69});
	((t_sphere *)data.objs)->mtx_inver = mtx_inverse(&data, ((t_sphere *)data.objs)->mtx_trans);


	// start_mlx(&data.canvas);
	data.ray.origin = (t_point){0, 0, -5, 1};
	light = set_light(&(t_point){0, 0.25, 0, 1}, &(t_tuple){1, 1, 1, 69});

	data.ray.direction = (t_vector){0, 0, 1, 0};
	check_intersections(&data, &(t_point){0, 0, 10, 1});
	if (data.first_hit)
	{
		light_vec(&((t_sphere *)data.first_hit->obj)->trans_ray, &light, &data);
		color = lighting(data.first_hit, &light);

		printf("point: %f %f %f\n", data.first_hit->point.x, data.first_hit->point.y, data.first_hit->point.z);
		printf("eye: %f %f %f\n", light.eyev.x, light.eyev.y, light.eyev.z);
		printf("normal: %f %f %f\n", light.normalv.x, light.normalv.y, light.normalv.z);
		printf("color: %f %f %f\n", color.x, color.y, color.z);

	}
	clear_ray_inter(&data);
	clear_objs(data.objs);


	// y = -1;
	// while (++y < HEIGTH)
	// {
	// 	x = -1;
	// 	while (++x < WIDTH)
	// 	{
	// 		w_x = map_x(x, -5, 5);		
	// 		w_y = map_y(y, -5, 5);		
	// 		check_intersections(&data, &(t_point){w_x, w_y, 5, 1});
	// 		if (data.first_hit)
	// 		{
	// 			light_vec(&((t_sphere *)data.first_hit->obj)->trans_ray, &light, &data);
	// 			color = lighting(data.first_hit, &light);
	// 			// write_pixel(&data.canvas, x, y, &color);
	// 		}
	// 		clear_ray_inter(&data);
	// 	}
	// }
	// mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
	// mlx_loop(data.canvas.mlx);
	// clear_objs(data.objs);
}
