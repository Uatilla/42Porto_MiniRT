/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:02:44 by uviana-a          #+#    #+#             */
/*   Updated: 2024/08/02 21:48:30 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(int argc, char **argv)
{
    //t_minirt    mrt;
    int         fd;
    t_point   p;
    t_point   p2;
    t_vector  v;
    t_vector  v2;
    t_color   c;
    t_point   res;
    float      value;

    fd = chk_input(argc, argv[1]);
    
    p = creating_point(1, 2, 3);
    printf("P: X(%f) Y(%f) Z(%f) W(%f)\n", p.x, p.y, p.z, p.w);
    p2 = creating_point(2, 3, 4);
    printf("P2: X(%f) Y(%f) Z(%f) W(%f)\n", p2.x, p2.y, p2.z, p2.w);
    printf("----------------\n");
    v = creating_vector(-1, -2, -3);
    printf("V: X(%f) Y(%f) Z(%f) W(%f)\n", v.x, v.y, v.z, v.w);
    v2 = creating_vector(2, 3, 4);
    printf("V2: X(%f) Y(%f) Z(%f) W(%f)\n", v2.x, v2.y, v2.z, v2.w);
    printf("----------------\n");
    c = creating_color(200, 113, 134);
    printf("C: X(%f) Y(%f) Z(%f) W(%f)\n", c.x, c.y, c.z, c.w);
    printf("----------------\n");
    value = magnitude(&v);
    //printf("RES: X(%f) Y(%f) Z(%f) W(%f)\n", res.x, res.y, res.z, res.w);
    printf("%f\n", value);
    return (0);
}
