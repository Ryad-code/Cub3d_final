#include "../../cub3D.h"

int	ft_strstr(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i])
	{
		if (str1[i] == str2[0])
		{
			while (str1[i + j] ==  str2[j])
				j++;
		}
		if (j >= ft_strlen(str2))
			return (0);
		i++;
	}
	return (-1);
}

int	ft_is_opt(char *opt, char *line)
{
	if (ft_strstr(line, opt) == 0)
		return (0);
	return (-1);
}

int	ft_count_lines(t_mlx *mlx, char *file)
{
	int	fd;
	int	nb_line;
	int	nb_empty;
	char	*line;

	fd = open(file, O_RDONLY);
	nb_line = 0;
	nb_empty = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_empty_line(line) == 0)
			nb_empty++;
		nb_line++;
		free(line);
	}
	close(fd);
	free(line);
	mlx->arg.nb_line = nb_line;
	mlx->arg.nb_empty = nb_empty;
	return (0);
}

int	ft_get_text(t_mlx *mlx, char *file)
{
	int	i;
	int	res;
	int	fd;
	char	*line;

	i = 0;
	res = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (ft_is_opt("NO", line) == 0)
		{
			mlx->arg.no = ft_strdup(line);
			res++;
		}
		else if (ft_is_opt("SO", line) == 0)
		{
			mlx->arg.so = ft_strdup(line);
			res++;
		}
		else if (ft_is_opt("WE", line) == 0)
		{
			mlx->arg.we = ft_strdup(line);
			res++;
		}
		else if (ft_is_opt("EA", line) == 0)
		{
			mlx->arg.ea = ft_strdup(line);
			res++;
		}
		else if (ft_is_opt("F ", line) == 0)
		{
			mlx->arg.f.str = ft_strdup(line);
			res++;
		}
		else if (ft_is_opt("C ", line) == 0)
		{
			mlx->arg.c.str = ft_strdup(line);
			res++;
		}
		if (res < 6)
			i++;
		free(line);
	}
	close(fd);
	free(line);
	if (res != 6)
		return (-1);
	return (i);
}

int	ft_empty_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_is_line(char *str)
{
	int i;

	i = 0;
	if (str == NULL || ft_strlen(str) == 0 || ft_empty_line(str) == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1' &&
			str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != 'E')
				return (-1);
		i++;
	}
	return (0);
}

void	ft_get_g_height(t_mlx *mlx, char *file)
{
	int	vide;
	int	fd;
	int	height;
	int	width;
	char	*line;

	vide = 0;
	fd = open(file, O_RDONLY);
	height = 0;
	width = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_is_line(line) == 0 && vide == 0)
		{
			if (ft_strlen(line) > width)
				width = ft_strlen(line);
			height++;
		}
		if (ft_is_line(line) != 0 && height > 0)
			vide = 1;
		free(line);
	}
	free(line);
	mlx->map.g_width = width;
	mlx->map.g_height = height;
	close(fd);
}

int	ft_get_map(t_mlx *mlx, char *file)
{
	int	i;
	int	res;
	int	fd;
	char *line;
	
	i = 0;
	res = 0;
	fd = open(file, O_RDONLY);
	line = NULL;
	mlx->map.grid = malloc(sizeof(char *) * (mlx->map.g_height + 1));
	if (mlx->map.grid == NULL)
		return (-1);
	while (get_next_line(fd, &line) && i < mlx->map.g_height)
	{
		if (ft_is_line(line) == 0)
		{	mlx->map.grid[i] = ft_strdup(line);
			i++;
		}
		free(line);
		res++;
	}
	mlx->map.grid[i] = NULL;
	free(line);
	close(fd);
	return (res);
}

int	ft_get_infos(t_mlx *mlx, char *file)
{
	int text;
	int map;
	int position;

	ft_count_lines(mlx, file);
	ft_get_g_height(mlx, file);
	if (mlx->arg.nb_line > (mlx->arg.nb_empty + mlx->map.g_height + 6))
		return(-1);
	if (mlx->map.g_height < 2 || mlx->map.g_width < 2)
		return (-1);
	text = ft_get_text(mlx, file);
	map = ft_get_map(mlx, file);
	position = ft_get_position(mlx);
	if (text < 0 || map < 0 || position < 0 || text > map)
		return (-1);
	return (0);
}
