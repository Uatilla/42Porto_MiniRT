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

/// @brief Find the intersection (scalar value) in a vector.
/// @param a Tuple to be multiplied.
/// @param sc Scalar value.
/// @return The tuple(point) in the scalar intersection.
t_tuple mult_tuple_scalar(t_tuple a, float sc)
{
    t_tuple res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    if (a.w != 999999 && b.w != 999999)
        res.w = a.w + b.w;
    else
        res.w = 999999;
    return(res);
}

int main(int argc, char **argv)
{
    //t_minirt    mrt;
    int         fd;
    point   p;
    point   p2;
    vector  v;
    vector  v2;
    color   c;
    point   res;

    fd = chk_input(argc, argv[1]);
    
    p = creating_point(1, -2, 3);
    printf("P: X(%f) Y(%f) Z(%f) W(%f)\n", p.x, p.y, p.z, p.w);
    p2 = creating_point(5, 6, 7);
    printf("P2: X(%f) Y(%f) Z(%f) W(%f)\n", p2.x, p2.y, p2.z, p2.w);
    printf("----------------\n");
    v = creating_vector(3, 2, 1);
    printf("V: X(%f) Y(%f) Z(%f) W(%f)\n", v.x, v.y, v.z, v.w);
    v2 = creating_vector(5, 6, 7);
    printf("V2: X(%f) Y(%f) Z(%f) W(%f)\n", v2.x, v2.y, v2.z, v2.w);
    printf("----------------\n");
    c = creating_color(200, 113, 134);
    printf("C: X(%f) Y(%f) Z(%f) W(%f)\n", c.x, c.y, c.z, c.w);
    printf("----------------\n");
    res = mult_tuple_scalar(p, 3.5);
    printf("RES: X(%f) Y(%f) Z(%f) W(%f)\n", res.x, res.y, res.z, res.w);


    
    


    return (0);
}
