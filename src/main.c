#include "../cub3D.h"

int main(int ac, char **av)
{
	t_mlx	mlx;

	mlx.frame = 1;

	ft_init_data(&mlx);
	printf("o = %d\n", ft_is_num(' '));
	if (ft_args(ac, av) < 0)
	{
		printf("Error1\n");
		return (-1);
	}
	if (ft_get_infos(&mlx, av[1]) < 0)
	{
		ft_free_data(&mlx);
		printf("Error2\n");
		return (-2);
	}
	if (ft_parse_text(&mlx) < 0)
	{
		ft_free_data(&mlx);
		printf("Error3\n");
		return (-3);
	}
	if (ft_parse_map(&mlx) < 0)
	{
		ft_free_data(&mlx);
		printf("Error4\n");
		return (-4);
	}
	if (ft_parse_colors(&mlx) < 0)
	{
		ft_free_data(&mlx);
		printf("Error5\n");
		return(-5);
	}
	ft_display_map(&mlx);
	mlx.mlx = mlx_init();//..............INIT WINDOW
	if (ft_init_texture(&mlx) < 0)
	{
		ft_free_data(&mlx);
		printf("Wrong texture paths\n");
		return (-6);
	}
	mlx.win = mlx_new_window(mlx.mlx, S_WIDTH, S_HEIGHT, "cub3D");

	mlx.buff01.img = mlx_new_image(mlx.mlx, S_WIDTH, S_HEIGHT);
	mlx.buff01.addr = mlx_get_data_addr(mlx.buff01.img, &mlx.buff01.bpp,
		&mlx.buff01.l_len, &mlx.buff01.endian);
//............................................................................
	ft_vector(&mlx, &mlx.buff01);//........................................3D DISPLAY
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.buff01.img, 0, 0);
	
	mlx_hook(mlx.win, 2, 1L<<0, ft_next_frame, &mlx);//....................KEY_HOOK
	mlx_loop(mlx.mlx);
	return (0);
}
