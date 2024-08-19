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


int	main(void)
{
	t_minirt	data;
	t_color		color;
	t_ray		ray;

	ft_memset(&data, 0, sizeof(data));

	parse_sphere(&data.world);
	data.world.sphere->mtx_inver = mtx_inverse(NULL, data.world.sphere->mtx_trans);

	parse_sphere(&data.world);
	mtx_scaling(data.world.sphere->mtx_trans, &(t_tuple){0.5, 0.5, 0.5, 1});
	data.world.sphere->mtx_inver = mtx_inverse(NULL, data.world.sphere->mtx_trans);

	set_light(&(t_point){0, 0.25, 0, 1}, &(t_color){1, 1, 1, 1}, &data.world);
	ray.origin = (t_point){0, 0, 0, 1};
	ray.direction = (t_vector){0, 0, 1, 0};
	data.ray = ray;

	color = color_at(&data);

	printf("point: %f %f %f\n", data.first_hit->point.x, data.first_hit->point.y, data.first_hit->point.z);
	printf("eyev: %f %f %f\n", data.world.light->eyev.x, data.world.light->eyev.y, data.world.light->eyev.z);
	printf("normalv: %f %f %f\n", data.world.light->normalv.x, data.world.light->normalv.y, data.world.light->normalv.z);

	printf("color: %f %f %f\n", color.r, color.g, color.b);

	clear_ray_inter(&data);
	clean_world(&data.world);
	return (0);
}




























// int	main(void)
// {
// 	t_minirt	data;
// 	t_light		light;
// 	t_color		color;
// 	int			x;
// 	int			y;
//
// 	ft_memset(&data, 0, sizeof(data));
// 	parse_objects(SP, &data);
// 	// mtx_scaling(((t_sphere *)data.objs)->mtx_trans, &(t_tuple){4, 4, 4, 1});
// 	((t_sphere *)data.objs)->mtx_inver = mtx_inverse(&data, ((t_sphere *)data.objs)->mtx_trans);
// 	data.camera = camera_construct(HEIGTH, WIDTH, PI / 2);
// 	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
// 	data.camera.inver = mtx_inverse(&data, data.camera.trans);
// 	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 69});
// 	start_mlx(&data.canvas);
// 	y = -1;
// 	while (++y < HEIGTH)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			data.ray = ray_for_pixel(&data.camera, x, y);
// 			check_intersections(&data);
// 			if (data.first_hit)
// 			{
// 				light_vec(&((t_sphere *)data.first_hit->obj)->trans_ray, &light, &data);
// 				color = lighting(data.first_hit, &light);
// 				write_pixel(&data.canvas, x, y, &color);
// 			}
// 			clear_ray_inter(&data);
// 		}
// 	}
// 	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
// 	printf("end\n");
// 	mlx_loop(data.canvas.mlx);
// }
