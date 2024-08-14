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
// nao esquecer de setar a origem da camera(ray) e depois a direcao;
// importante chamar clear_ray_inter depoins de check intersection;
// comecar com start_mlx, e nao esquecer de chamar no fim:
// 		mlx_put_image_to_window e mlx_loop
int	main(void)
{
	t_minirt	data;
	float		t[2];
	t_ray		trans_ray;
	t_matrix	*inver_trans;

	ft_memset(&data, 0, sizeof(data));
	data.ray.origin = (t_point){0, 0, -5, 1};
	data.ray.direction = (t_vector){0, 0, 1, 0};
	parse_objects(SP, &data);
	mtx_scaling(((t_sphere *)data.objs)->trans, &(t_tuple){2,2,2,69});
	
	inver_trans = mtx_inverse(&data, ((t_sphere *)data.objs)->trans);
	trans_ray = ray_trasform(&data.ray, inver_trans);

	// printf("origin %f %f %f\n", trans_ray.origin.x, trans_ray.origin.y, trans_ray.origin.z);
	// printf("direct %f %f %f\n", trans_ray.direction.x, trans_ray.direction.y, trans_ray.direction.z);
	ray_intersections(&data, data.objs, &trans_ray);

	if (data.first_hit)
	{
		if (data.first_hit->count == 1)
			printf("one hit\n");
		if (data.first_hit->count == 2)
			printf("two hit\n");
	}
	else
		printf("not hit\n");
}
