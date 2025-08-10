/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalkhate <nalkhate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:14:33 by nalkhate          #+#    #+#             */
/*   Updated: 2025/08/10 15:53:50 by nalkhate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/libft/libft.h"
# include "../srcs/mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define WIN_W 800
# define WIN_H 600

/* keycodes: works on both Linux(X11) and macOS */
# define KEY_ESC_L 65307
# define KEY_ESC_M 53

/* declare GNL if you keep it inside libft.a */
char	*get_next_line(int fd);

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_scene
{
	t_color	floor_c;
	t_color	ceil_c;
}	t_scene;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	*scn;
}	t_mlx;

/* parsing */
int		parse_scene(const char *path, t_scene *scn);

/* mlx / render / hooks */
int		init_mlx(t_mlx *m, t_scene *scn);
void	destroy_and_exit(t_mlx *m, int code);
void	render_frame(t_mlx *m);
void	put_pixel(t_img *im, int x, int y, int color);
void	set_hooks(t_mlx *m);
int		on_key(int key, t_mlx *m);
int		on_close(t_mlx *m);

#endif
