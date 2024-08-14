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
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	parse_objects(SP, &data);

	mtx_translation(((t_sphere *)data.objs)->transform, &(t_tuple){2, 3, 4, 69});
	for (t_sphere *ptr = data.objs; ptr; ptr = ((t_sphere *)ptr)->next)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("%f ", ptr->transform->mtx[i][j]);
			}
			printf("\n");
		}
	}
}



































// nao esquecer de chamar ft_memeset para data;
// nao esquecer de setar a origem da camera(ray) e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
// comecar com start_mlx, e nao esquecer de chamar no fim:
// 		mlx_put_image_to_window e mlx_loop
// int	main(void)
// {
// 	t_minirt 	data;
// 	t_light		light;
// 	int			y;
// 	int			x;
// 	float		world_x;
// 	float		world_y;
// 	t_vector	eye;
// 	t_color		color;
//
// 	t_matrix	*mtx_a;
// 	t_matrix	*mtx_inv;
// 	t_point		pt;
// 	t_point		pt_res;
//
// 	t_vector	vec;
// 	t_vector	vec_cal;
// 	t_vector	vec_res;
//
//
//
// 	ft_memset(&data, 0, sizeof(data));
// 	start_mlx(&data.canvas);
// 	parse_objects(SP, &data);
//
// 	light = set_light(&(t_point){-10,10,-10,1}, &(t_color){1,1,1,999999});
// 	data.ray.origin = (t_point){0,0,-5,1};
// 	y = -1;
// 	while (++y < HEIGTH)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			world_x = map_x(x, -5, 5);
// 			world_y = map_y(y, -5, 5);
// 			check_intersections(&data, &(t_point){world_x, world_y, 5, 1});
// 			if (data.ray.first_hit)
// 			{
// 				//data.ray.first_hit->point = mtx_mult_tuple(mtx_a, &data.ray.first_hit->point);
// 				// light_vec(&data.ray, &light);
// 				// color = lighting(data.ray.first_hit, &light);
// 				write_pixel(&data.canvas, x, y, &(t_color){1,0,0,1});
// 			}
// 			clear_ray_inter(&data);
// 		}
// 	}
//
// 	mtx_a = mtx_create(&data, 4 ,4);
// 	fill_idnty_mtx(mtx_a);
// 	pt = creating_point(-1, 1, 1);
// 	mtx_scaling(mtx_a, &pt);
// 	mtx_inv = mtx_inverse(&data, mtx_a);
// 	mtx_print(mtx_inv);
//
// 	vec_cal = creating_vector(2, 3, 4);
// 	vec_res = mtx_mult_tuple(mtx_inv, &vec_cal);
// 	printf("pt X:%f Y:%f Z:%f W:%f\n", vec_res.x, vec_res.y, vec_res.z, vec_res.w);
//
// 	printf("Degree: %f, Radians: %f\n", 180.00, degree_to_rad(180.00));
//
//
// 	clean_matrix(&data, mtx_inv, 0);
// 	mlx_put_image_to_window(data.canvas.mlx, data.canvas.win, data.canvas.img, 0, 0);
// 	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
// 	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
// 	mlx_loop(data.canvas.mlx);
// 	clear_exit(&data, 0);
// }
