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

	t_material floor;
	floor.color = (t_color){1, 0.9, 0.9, 69};
	floor.ambient = 0.1;
	floor.specular = 0;
	floor.shininess = 200;
	floor.diffuse = 0.7;

	parse_sphere(&data.world, &floor);
	mtx_scaling(data.world.sphere->mtx_trans, &(t_point){10, 0.01, 10, 1});
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	t_material left_wall;
	left_wall.color = (t_color){1, 0.9, 0.9, 69};
	left_wall.specular = 0;
	left_wall.ambient = 0.1;
	left_wall.shininess = 200;
	left_wall.diffuse = 0.7;

	t_matrix *translation_left_wall = mtx_create(&data, 4, 4);
	mtx_fill(translation_left_wall);
	mtx_translation(translation_left_wall, &(t_point){0, 0, 5, 1});

	t_matrix *rot_y = mtx_create(&data, 4, 4);
	mtx_fill(rot_y);
	mtx_rotation_y(rot_y, -PI / 4);

	t_matrix *rot_x = mtx_create(&data, 4, 4);
	mtx_fill(rot_x);
	mtx_rotation_x(rot_x, PI / 2);

	t_matrix *scaling_left_wall = mtx_create(&data, 4, 4);
	mtx_fill(scaling_left_wall);
	mtx_scaling(scaling_left_wall, &(t_point){10, 0.01, 10, 1});

	parse_sphere(&data.world, &left_wall);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, translation_left_wall);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, rot_y);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, rot_x);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, scaling_left_wall);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	t_material right_wall;
	right_wall.color = (t_color){1, 0.9, 0.9, 69};
	right_wall.specular = 0;
	right_wall.ambient = 0.1;
	right_wall.shininess = 200;
	right_wall.diffuse = 0.7;

	t_matrix *translation_right_wall = mtx_create(&data, 4, 4);
	mtx_fill(translation_right_wall);
	mtx_translation(translation_right_wall, &(t_point){0, 0, 5, 1});

	t_matrix *rot_right_y = mtx_create(&data, 4, 4);
	mtx_fill(rot_right_y);
	mtx_rotation_y(rot_right_y, PI / 4);

	t_matrix *rot_right_x = mtx_create(&data, 4, 4);
	mtx_fill(rot_right_x);
	mtx_rotation_x(rot_right_x, PI / 2);

	t_matrix *scaling_right_wall = mtx_create(&data, 4, 4);
	mtx_fill(scaling_right_wall);
	mtx_scaling(scaling_right_wall, &(t_point){10, 0.01, 10, 1});


	parse_sphere(&data.world, &right_wall);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, translation_right_wall);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, rot_right_y);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, rot_right_x);
	data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, scaling_right_wall);
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);


	t_material middle;
	middle.color = (t_tuple){0.1, 1, 0.5, 1};
	middle.diffuse = 0.7;
	middle.specular = 0.3;
	middle.ambient = 0.1;
	middle.shininess = 200;

	parse_sphere(&data.world, &middle);
	mtx_translation(data.world.sphere->mtx_trans, &(t_point){-0.5, 1, 0.5, 1});
	data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);

	t_material right;
	right.color = (t_color){0.5, 1, 0.1, 69};
	right.diffuse = 0.7;
	right.specular = 0.3;
	right.ambient = 0.1;
	right.shininess = 200;

	// t_matrix *scaling_right_ball = mtx_create(&data, 4, 4);
	// mtx_fill(scaling_right_ball);
	// mtx_scaling(scaling_right_ball, &(t_point){0.5, 0.5, 0.5, 1});

	// parse_sphere(&data.world, &right);
	// mtx_translation(data.world.sphere->mtx_trans, &(t_point){1.5, 0.5, -0.5, 1});
	// data.world.sphere->mtx_trans = mtx_multiply(&data, data.world.sphere->mtx_trans, scaling_right_ball);
	// data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);

	t_material	left;
	left.color = (t_color){1, 0.8, 0.1, 1};
	left.diffuse = 0.7;
	left.specular = 0.3;
	left.ambient = 0.1;
	left.shininess = 200;

	// parse_sphere(&data.world, &left);
	// mtx_translation(data.world.sphere->mtx_trans, &(t_point){-1.5, 0.33, -0.75, 1});
	// mtx_scaling(data.world.sphere->mtx_trans, &(t_point){0.33, 0.33, 0.33, 1});
	// data.world.sphere->mtx_inver = mtx_inverse(&data, data.world.sphere->mtx_trans);

	set_light(&(t_point){-10, 10, -10, 1}, &(t_color){1, 1, 1, 1}, &data.world);

	data.camera = camera_construct(WIDTH, HEIGTH, PI / 3);
	clean_matrix(&data, data.camera.trans, 0);
	data.camera.trans = view_transformation(&(t_point){0, 1.5, -5, 1}, &(t_point){0, 1, 0, 1}, &(t_vector){0, 1, 0, 0});
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
	while (++y < data->camera.vsize - 1)
	{
		x = -1;
		while (++x < data->camera.hsize - 1)
		{
			data->ray = ray_for_pixel(&data->camera, x, y);
			color_at(data, x, y);
		}
	}
	ft_printf("end render\n");
	mlx_put_image_to_window(data->canvas.mlx, data->canvas.win, data->canvas.img, 0, 0);
	mlx_loop(data->canvas.mlx);
}
