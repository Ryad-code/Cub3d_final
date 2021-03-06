/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaouedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:23:43 by mlaouedj          #+#    #+#             */
/*   Updated: 2021/11/05 13:27:30 by mlaouedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(int ac, char **av)
{
	t_mlx	mlx;

	mlx.frame = 1;
	ft_init_data(&mlx);
	if (ft_checking(&mlx, ac, av) < 0)
		return (-1);
	mlx.mlx = mlx_init();
	if (ft_init_texture(&mlx) < 0)
	{
		ft_free_data(&mlx);
		printf("Wrong texture paths\n");
		return (-1);
	}
	mlx.win = mlx_new_window(mlx.mlx, S_WIDTH, S_HEIGHT, "cub3D");
	mlx.buff01.img = mlx_new_image(mlx.mlx, S_WIDTH, S_HEIGHT);
	mlx.buff01.addr = mlx_get_data_addr(mlx.buff01.img, &mlx.buff01.bpp,
			&mlx.buff01.l_len, &mlx.buff01.endian);
	ft_vector_1(&mlx, &mlx.buff01);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.buff01.img, 0, 0);
	mlx_hook(mlx.win, 33, (1L << 17), ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, ft_next_frame, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
