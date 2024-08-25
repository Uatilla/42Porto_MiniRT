/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/23 19:24:05 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


// int	main(void)
// {
// 	t_point p = (t_point){1, 0, 1, 1};
//
// 	t_matrix *A;
// 	t_matrix *B;
// 	t_matrix *C;
// 	t_matrix *T;
//
// 	A = mtx_create(NULL, 4, 4);
// 	fill_idnty_mtx(A);
// 	mtx_rotation_x(A, PI / 2);
//
// 	B = mtx_create(NULL, 4, 4);
// 	fill_idnty_mtx(B);
// 	mtx_scaling(B, &(t_point){5, 5, 5, 1});
//
// 	C = mtx_create(NULL, 4, 4);
// 	fill_idnty_mtx(C);
// 	mtx_translation(C, &(t_point){10, 5, 7, 1});
//
//
// 	T = mtx_create(NULL, 4, 4);
// 	fill_idnty_mtx(T);
// 	T = mtx_multiply(NULL, A, T);
// 	T = mtx_multiply(NULL, B, T);
// 	T = mtx_multiply(NULL, C, T);
//
// 	p = mtx_mult_tuple(T, &p);
//
// 	printf("%f %f %f\n", p.x, p.y, p.z);
// }
















// int	main(void)
// {
// 	t_minirt	data;
// 	t_color		color;
//
// 	ft_memset(&data, 0, sizeof(data));
//
// 	t_material	m;
// 	m.color = (t_color){0.8, 1.0, 0.6, 1};
// 	m.diffuse = 0.7;
// 	m.specular = 0.2;
// 	m.ambient = 0.1;
// 	m.shininess = 200;
//
// 	parse_shape(&data.world, &m, SP);
// 	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
//
//
// 	t_matrix *sc = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(sc);
// 	mtx_scaling(sc, &(t_point){0.5, 0.5, 0.5, 1});
//
// 	parse_shape(&data.world, &m, SP);
// 	data.world.objs->mtx_trans = mtx_multiply(&data, data.world.objs->mtx_trans, sc);
// 	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
//
//
// 	set_light(&(t_point){0, 0.25, 0, 1}, &(t_color){1, 1, 1, 1}, &data.world);
//
// 	data.ray.origin = (t_point){0, 0, 0, 1};
// 	data.ray.direction = (t_vector){0, 0, 1, 0};
//
// 	check_intersections(&data);
// 	if (data.first_hit)
// 	{
// 		printf("hit: %f\n", data.first_hit->hit);
// 		printf("count: %i\n", data.xs.count);
// 		for (int i = 0; i < data.xs.count; i++)
// 			printf("%f\n", data.xs.arr[i]);
//
// 		light_vec(&data.first_hit->obj->trans_ray, data.world.light, &data);
// 		printf("\n");
// 		printf("point: %f %f %f\n", data.first_hit->point.x, data.first_hit->point.y, data.first_hit->point.z);
// 		printf("eyev: %f %f %f\n", data.world.light->eyev.x, data.world.light->eyev.y, data.world.light->eyev.z);
// 		printf("normalv: %f %f %f\n", data.world.light->normalv.x, data.world.light->normalv.y, data.world.light->normalv.z);
//
// 		if (data.world.light->inside)
// 			printf("inside true\n");
// 		else
// 			printf("inside false\n");
//
// 		color = lighting(data.first_hit, data.world.light);
// 		printf("\n");
// 		printf("color: %f %f %f\n", color.r, color.g, color.b);
// 	}
// }












//
// int	main(void)
// {
// 	t_minirt	data;
//
// 	ft_memset(&data, 0, sizeof(data));
// 	start_mlx(&data.canvas);
//
// 	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);
//
// 	t_material	m;
// 	m.color = (t_color){0.8, 1.0, 0.6, 1};
// 	m.diffuse = 0.7;
// 	m.specular = 0.2;
// 	m.ambient = 0.1;
// 	m.shininess = 200;
//
// 	t_matrix *sc = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(sc);
// 	mtx_scaling(sc, &(t_point){0.5, 0.5, 0.5, 1});
//
// 	t_material	m_2;
// 	m_2.color = (t_color){0.3, 5.0, 0.6, 1};
// 	m_2.diffuse = 0.7;
// 	m_2.specular = 0.2;
// 	m_2.ambient = 0.1;
// 	m_2.shininess = 200;
//
// 	parse_shape(&data.world, &m, SP);
// 	// data.world.objs->mtx_trans = mtx_multiply(&data, sc, data.world.objs->mtx_trans);
// 	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
//
//
// 	t_matrix *rot;
// 	rot = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(rot);
// 	mtx_rotation_x(rot, PI / 2);
//
// 	t_matrix *trans;
// 	trans = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(trans);
// 	mtx_translation(trans, &(t_point){0, 0, 5, 1});
//
// 	parse_shape(&data.world, &m, PL);
// 	// data.world.objs->mtx_trans = mtx_multiply(&data, rot, data.world.objs->mtx_trans);
// 	// data.world.objs->mtx_trans = mtx_multiply(&data, trans, data.world.objs->mtx_trans);
// 	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
//
// 	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
// 	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
// 	data.camera.inver = mtx_inverse(&data, data.camera.trans);
// 	render(&data);
// }
//





























int	main(void)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));

	t_material floor;
	floor.color = (t_color){1, 0.9, 0.9, 1};
	floor.specular = 0;
	floor.shininess = 200;
	floor.diffuse = 0.7;
	floor.ambient = 0.1;

	t_matrix	*floor_sc = mtx_create(&data, 4, 4);
	fill_idnty_mtx(floor_sc);
	mtx_scaling(floor_sc, &(t_point){10, 0.01, 10});

	parse_shape(&data.world, &floor, SP);
	data.world.objs->mtx_trans = mtx_multiply(&data, floor_sc, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans


}
