/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/18 22:01:51 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_camera	camera_construct(size_t hsize, size_t vsize, float	vof);

int	main(void)
{
	t_camera	camera;

	camera = camera_construct(125, 200, PI/2);

	printf("hsize: %lu\n", camera.hsize);
	printf("vsize: %lu\n", camera.vsize);
	printf("vof: %f\n", camera.vof);
	printf("half_width: %f\n", camera.half_width);
	printf("half_height: %f\n", camera.half_height);
	printf("pixel_size: %f\n", camera.pixel_size);

	// for (int i = 0; i < 4; i++)
	// {
	// 	for (int j = 0; j < 4; j++)
	// 		printf("%f ", camera.trans->mtx[i][j]);
	// 	printf("\n");
	// }

	clean_matrix(NULL, camera.trans, 0);
	return (0);
}

t_camera	camera_construct(size_t hsize, size_t vsize, float	vof)
{
	t_camera	camera;
	float		half_view;
	float		aspect;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.vof = vof;
	camera.trans = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(camera.trans);
	half_view = tan(vof / 2);
	aspect = (float)hsize / (float)vsize;
	printf("half_view: %f\n", half_view);
	printf("aspect: %f\n", aspect);
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / hsize;
	return (camera);
}

















// nao esquecer de chamar ft_memeset para data;
// nao esquecer de setar a origem do ray e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
// comecar com start_mlx, e nao esquecer de chamar no fim:
// 		mlx_put_image_to_window e mlx_loop
// int	main(void)
// {
// 	t_minirt	data;
// 	t_light		light;
// 	t_color		color;
// 	int			x;
// 	int			y;
// 	float		w_x;
// 	float		w_y;
//
//
// 	ft_memset(&data, 0, sizeof(data));
//
// 	parse_objects(SP, &data);
// 	((t_sphere *)data.objs)->mtx_inver = mtx_inverse(&data, ((t_sphere *)data.objs)->mtx_trans);
//
// 	parse_objects(SP, &data);
// 	mtx_scaling(((t_sphere *)data.objs)->mtx_trans, &(t_point){0.5, 0.5, 0.5, 1});
// 	((t_sphere *)data.objs)->mtx_inver = mtx_inverse(&data, ((t_sphere *)data.objs)->mtx_trans);
//
//
//
// 	start_mlx(&data.canvas);
// 		data.ray.origin = (t_point){0, 0, -5, 1};
// 	// data.ray.direction = (t_vector){0, 0, 1, 0};
//
// 	light = set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1});
//
// 	check_intersections(&data, &(t_point){0, 0, 10, 1});
//
// 	// for (size_t i = 0; i < data.xs.count; i++)
// 	// 	printf("%f ", data.xs.arr[i]);
// 	// printf("\n");
// 	// printf("\n");
// 	//
// 	//
// 	// for (t_intersections *ptr = data.inter; ptr; ptr = ptr->next)
// 	// {
// 	// 	printf("%f %f\n", ptr->t[0], ptr->t[1]);
// 	// 	printf("hit: %f", ptr->hit);
// 	// 	printf("\n");
// 	// }
// 	// printf("\n");
// 	//
// 	// printf("first hit :%f\n\n", data.first_hit->hit);
// 	// 
// 	// if (data.first_hit)
// 	// {
// 	// 	printf("first t: %f\n", data.first_hit->hit);
// 	// 	light_vec(&((t_sphere *)data.first_hit->obj)->trans_ray, &light, &data);
// 	// 	color = lighting(data.first_hit, &light);
// 	//
// 	// 	printf("point: %f %f %f\n", data.first_hit->point.x, data.first_hit->point.y, data.first_hit->point.z);
// 	// 	printf("eye: %f %f %f\n", light.eyev.x, light.eyev.y, light.eyev.z);
// 	// 	printf("normal: %f %f %f\n", light.normalv.x, light.normalv.y, light.normalv.z);
// 	// 	printf("\n");
// 	// 	printf("color: %f %f %f\n", color.r, color.g, color.b);
// 	//
// 	// }
// 	// clear_ray_inter(&data);
// 	// clear_objs(data.objs);
//
//
// 	y = -1;
// 	while (++y < HEIGTH)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			w_x = map_x(x, -5, 5);		
// 			w_y = map_y(y, -5, 5);		
// 			check_intersections(&data, &(t_point){w_x, w_y, 5, 1});
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
// 	mlx_loop(data.canvas.mlx);
// 	clear_objs(data.objs);
// }
