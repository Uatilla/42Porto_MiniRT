/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/07/30 20:02:46 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool    is_tuple_equal(t_tuple a, t_tuple b)
{
    printf("a.x: %f - b.x: %f\n", a.x, b.x);
    return((a.x - b.x) < EPSILON\
        && (a.y - b.y) < EPSILON\
        && (a.z - b.z) < EPSILON);
}

int main()
{
    point   p;
    vector  v;
    color   c;

    p = creating_point(1, 2, 3);
    printf("Point: %d\n", is_point(p));
    printf("----------------\n");
    v = creating_vector(2, 3, 4);
    printf("Vector: %d\n", is_vector(v));
    printf("----------------\n");
    c = creating_color(200, 113, 134);
    printf("Color: %d\n", is_color(c));

    printf("Tuple: %d\n", is_tuple_equal(p, v));
    

    printf("%f\n", EPSILON);
    return (0);
}
