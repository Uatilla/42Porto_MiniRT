/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/03 17:40:30 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(void)
{
	t_minirt	data;

	data.ray.origin = (t_tuple){{2,3,4,1}};
	data.ray.direction = (t_tuple){{1,0,0,0}};

	t_tuple	pos = position(&data.ray, 2.5);
	printf("%f, %f, %f, %f\n", pos.x, pos.y, pos.z, pos.w);
    return (0);
}
