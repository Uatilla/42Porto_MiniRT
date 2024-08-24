/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/22 16:58:48 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*void	set_scene(t_minirt *mrt, int fd)
{
	mrt->world.
}*/

int	main(int argc, char **argv)
{
	int			fd;
	t_minirt	data;

	ft_memset(&data, 0, sizeof(data));
	fd = chk_input(&data, argc, argv[1]);
	//set_scene(&data, fd);

	start_mlx(&data.canvas);
	data.ray.origin = (t_point){0, 0, -5, 1};
	mlx_hook(data.canvas.win, 17, 0L, close_window, &data);
	mlx_key_hook(data.canvas.win, &handle_key_event, &data);
	mlx_loop(data.canvas.mlx);
	clear_exit(&data, 0);
}