/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/18 20:55:25 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_matrix	*view_transformation(t_point *from, t_point *to, t_vector *up);
t_matrix	*view_orientation(t_vector *left, t_vector *up, t_vector *forward);

int	main(void)
{
	t_matrix	*view;

	view = view_transformation(&(t_point){1, 3, 2, 1}, &(t_point){4, -2, 8, 1}, &(t_point){1, 1, 0, 0});

	for (int i = 0; i < 4; i++)
	{
		for (int y = 0; y < 4; y++)
		{
			printf("%f ", view->mtx[i][y]);
		}
		printf("\n");
	}

	clean_matrix(NULL, view, 0);
}

t_matrix	*view_transformation(t_point *from, t_point *to, t_vector *up)
{
	t_view		view;
	t_matrix	*orientation;
	t_matrix	*trans;
	t_matrix	*ret;

	view.forward = subtrac_tuples(to, from);
	view.forward = normalize(&view.forward);
	view.upn = normalize(up);
	view.left = cross_product(&view.forward, &view.upn);
	view.true_uper = cross_product(&view.left, &view.forward);
	orientation = view_orientation(&view.left, &view.true_uper, &view.forward);
	trans = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(trans);
	mtx_translation(trans, &(t_point){-from->x, -from->y, -from->z, 1});
	ret = mtx_multiply(NULL, orientation, trans);
	clean_matrix(NULL, orientation, 0);
	clean_matrix(NULL, trans, 0);
	return (ret);
}

t_matrix	*view_orientation(t_vector *left, t_vector *up, t_vector *forward)
{
	t_matrix	*orientation;

	orientation = mtx_create(NULL, 4, 4);
	orientation->mtx[0][0] = left->x;
	orientation->mtx[0][1] = left->y;
	orientation->mtx[0][2] = left->z;
	orientation->mtx[1][0] = up->x;
	orientation->mtx[1][1] = up->y;
	orientation->mtx[1][2] = up->z;
	orientation->mtx[2][0] = -forward->x;
	orientation->mtx[2][1] = -forward->y;
	orientation->mtx[2][2] = -forward->z;
	orientation->mtx[3][3] = 1;
	return (orientation);
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
