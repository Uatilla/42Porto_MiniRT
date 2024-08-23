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

int	main(void)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);

	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);

	t_material	m;
	m.color = (t_color){0.8, 1.0, 0.6, 1};
	m.diffuse = 0.7;
	m.specular = 0.2;
	m.ambient = 0.1;
	m.shininess = 200;

	t_matrix *sc = mtx_create(&data, 4, 4);
	fill_idnty_mtx(sc);
	mtx_scaling(sc, &(t_point){0.5, 0.5, 0.5, 1});

	t_material	m_2;
	m_2.color = (t_color){0.8, 4.0, 0.6, 1};
	m_2.diffuse = 0.7;
	m_2.specular = 0.2;
	m_2.ambient = 0.1;
	m_2.shininess = 200;

	parse_shape(&data.world, &m, SP);
	data.world.objs->mtx_trans = mtx_multiply(&data, sc, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);


	t_matrix *rot;
	rot = mtx_create(&data, 4, 4);
	fill_idnty_mtx(rot);
	mtx_rotation_x(rot, PI / 2);

	parse_shape(&data.world, &m, PL);
	data.world.objs->mtx_trans = mtx_multiply(&data, rot, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	// data.ray.origin = (t_point){0, 0, -5, 1};
	// data.ray.direction = (t_vector){0, 0, 1, 0};
	//
	// check_intersections(&data);
	// if (data.first_hit)
	// {
	// 	printf("x.count: %d\n", data.xs.count);
	// 	for (int i = 0; i < data.xs.count; i++)
	// 		printf("%f\n", data.xs.arr[i]);
	// 	printf("\n");
	// }










	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);
	render(&data);
	
}
