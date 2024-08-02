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

// t_tuple sum_tuples(t_tuple a, t_tuple b)
// {
//     t_tuple res_tuple = 
// }

int main(int argc, char **argv)
{
    //t_minirt    mrt;
    int         fd;
    point   p;
    vector  v;
    color   c;
    point   res;

    fd = chk_input(argc, argv[1]);
    
    p = creating_point(3, -2, 5);
    printf("P: X(%f) Y(%f) Z(%f) W(%f)\n", p.x, p.y, p.z, p.w);
    printf("----------------\n");
    v = creating_vector(-2, 3, 1);
    printf("V: X(%f) Y(%f) Z(%f) W(%f)\n", v.x, v.y, v.z, v.w);
    printf("----------------\n");
    c = creating_color(200, 113, 134);
    printf("C: X(%f) Y(%f) Z(%f) W(%f)\n", c.x, c.y, c.z, c.w);
    printf("----------------\n");
    printf("Operating a Sum:\n");
    // res = sum_tuples(p, v);
    
    


    return (0);
}
