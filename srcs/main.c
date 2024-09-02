/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/29 17:16:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// int main(void)
// {
// 	t_minirt	data;
// 	t_pattern	pattern;
// 	t_color		color;
//
// 	ft_memset(&data, 0, sizeof(data));
//
// 	t_matrix *trans;
// 	trans = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(trans);
// 	mtx_translation(trans, &(t_point){0.5, 1, 1.5, 1});
//
// 	t_material	m;
// 	m.color = (t_color){0.8, 0.5, 0.9, 9999};
// 	m.ambient = 0.1;
// 	m.diffuse = 0.9;
// 	m.specular = 0.9;
// 	m.shininess = 200;
// 	m.pattern = stripe_pattern(&(t_color){1, 1, 1, 1}, &(t_color){0, 0, 0, 1}, PC);
// 	m.pattern.trans = mtx_multiply(&data, trans, m.pattern.trans);
// 	m.pattern.inver = mtx_inverse(&data, m.pattern.trans);
//
// 	t_matrix *T;
// 	T = mtx_create(&data, 4, 4);
// 	fill_idnty_mtx(T);
// 	mtx_scaling(T, &(t_tuple){2, 2, 2, 2});
//
// 	parse_shape(&data.world, &m, SP);
// 	data.world.objs->mtx_trans = mtx_multiply(&data, T, data.world.objs->mtx_trans);
// 	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);
//
// 	color = pattern_at(&m.pattern, &(t_point){2.5, 3, 3.5, 1}, data.world.objs, data.world.objs->material.pattern.type);
//
// 	printf("%f %f %f\n", color.r, color.g, color.b);
//
// 	clean_sphere(data.world.objs);
// }






























int	main(void)
{
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	start_mlx(&data.canvas);

	t_material m;
	m.color = (t_color){0.8, 0.5, 0.9, 9999};
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	m.pattern = stripe_pattern(&(t_color){0.1, 0.25, 0.9, 1}, &(t_color){0.42, 0.81, 0.1, 1}, PC);
	mtx_scaling(m.pattern.trans, &(t_point){0.2, 0.2, 0.2, 1});
	m.pattern.inver = mtx_inverse(&data, m.pattern.trans);

	t_matrix *ball_sc_1;
	ball_sc_1 = mtx_create(&data, 4, 4);
	fill_idnty_mtx(ball_sc_1);
	mtx_translation(ball_sc_1, &(t_point){0.6, 0, 0, 1});

	parse_shape(&data.world, &m, SP);
	data.world.objs->mtx_trans = mtx_multiply(&data, ball_sc_1, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	t_material m_2;
	m_2.color = (t_color){0.1, 0.5, 0.9, 9999};
	m_2.ambient = 0.1;
	m_2.diffuse = 0.9;
	m_2.specular = 0.9;
	m_2.shininess = 200;
	m_2.pattern = stripe_pattern(&(t_color){0.5, 0.25, 0.5, 1}, &(t_color){0.2, 1, 1, 1}, STR);
	mtx_scaling(m_2.pattern.trans, &(t_point){0.2, 0.2, 0.2, 1});
	m_2.pattern.inver = mtx_inverse(&data, m_2.pattern.trans);

	t_matrix *ball_trans;
	ball_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(ball_trans);
	mtx_translation(ball_trans, &(t_point){-2, -0.6, 0, 1});

	t_matrix *ball_sc;
	ball_sc = mtx_create(&data, 4, 4);
	fill_idnty_mtx(ball_sc);
	mtx_scaling(ball_sc, &(t_point){0.33, 0.33, 0.33, 1});

	t_matrix *ball_rot;
	ball_rot = mtx_create(&data, 4, 4);
	fill_idnty_mtx(ball_rot);
	mtx_rotation_y(ball_rot, PI / 2);

	parse_shape(&data.world, &m_2, SP);
	data.world.objs->mtx_trans = mtx_multiply(&data, ball_rot, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, ball_sc, data.world.objs->mtx_trans);
	data.world.objs->mtx_trans = mtx_multiply(&data, ball_trans, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	t_material floor;
	floor.color = (t_color){0.8, 0.6, 0.5, 9999};
	floor.ambient = 0.1;
	floor.diffuse = 0.9;
	floor.specular = 0.9;
	floor.shininess = 200;
	floor.pattern = stripe_pattern(&(t_color){1, 0, 0.5, 1}, &(t_color){0.5, 1, 0, 1}, STR);
	floor.pattern.inver = mtx_inverse(&data, floor.pattern.trans);

	t_matrix *floor_trans;
	floor_trans = mtx_create(&data, 4, 4);
	fill_idnty_mtx(floor_trans);
	mtx_translation(floor_trans, &(t_point){0, -1, 0, 1});

	parse_shape(&data.world, &floor, PL);
	data.world.objs->mtx_trans = mtx_multiply(&data, floor_trans, data.world.objs->mtx_trans);
	data.world.objs->mtx_inver = mtx_inverse(&data, data.world.objs->mtx_trans);

	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);
	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	data.camera.trans = view_transformation(&(t_point){0, 0, -5, 1}, &(t_point){0, 0, 0, 1}, &(t_vector){0, 1, 0, 0});
	data.camera.inver = mtx_inverse(&data, data.camera.trans);
	render(&data);
	clean_world(&data.world);
	clean_matrix(&data, data.camera.trans, 0);
	clean_matrix(&data, data.camera.inver, 0);
}
