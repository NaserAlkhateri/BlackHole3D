/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amersha <amersha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:14:33 by nalkhate          #+#    #+#             */
/*   Updated: 2025/08/30 14:06:28 by amersha          ###   ########.fr       */
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

# define WIN_W 800
# define WIN_H 600

/* macOS keycodes */
# define KEY_ESC_M    53
# define KEY_LEFT_M   123
# define KEY_RIGHT_M  124
# define KEY_W_M      13
# define KEY_A_M      0
# define KEY_S_M      1
# define KEY_D_M      2

/* X11 keycodes */
# define KEY_ESC_L    65307
# define KEY_LEFT_L   65361
# define KEY_RIGHT_L  65363
# define KEY_W_L      119
# define KEY_A_L      97
# define KEY_S_L      115
# define KEY_D_L      100

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
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	char	**map;
	int		map_w;
	int		map_h;
	double	px;
	double	py;
	double	dirx;
	double	diry;
	double	plx;
	double	ply;
}	t_scene;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_scene	*scn;
}	t_mlx;

typedef struct s_ps
{
	int		fd;
	char	*ln;
	int		got_f;
	int		got_c;
	char	*acc;
	int		r;
	int		map_acc_result;
	int		in_map;
	char	*loop_res;
}	t_ps;

char		*get_next_line(int fd);
/* parsing / map */
const char	*parse_scene(const char *path, t_scene *scn);
int			map_accumulate(char **acc, char *line, int *in_map);
int			map_finalize(t_scene *scn, char *acc);
int			parse_rgb(const char *s, t_color *out);
void		rstrip(char *s);
int			parse_texline(char *ln, t_scene *scn);
const char	*handle_line(t_ps *ps, t_scene *scn);
const char	*validate_map(t_scene *scn);
void		init_player_from_map(t_scene *s);
void		invalid_cub(t_ps *ps);
int			is_map_char(char c);
const char	*handle_tex_phase(t_ps *ps, t_scene *scn, int *handled);
const char	*handle_color_phase(t_ps *ps, t_scene *scn, int *handled);
const char	*handle_map_phase(t_ps *ps);
char		*skip_ws(char *p);
/* textures */
const char	*load_textures(t_mlx *m, t_scene *scn);
void		free_textures(t_mlx *m);

/* mlx / render / hooks */
int			init_mlx(t_mlx *m, t_scene *scn);
void		destroy_and_exit(t_mlx *m, int code);
void		render_frame(t_mlx *m);
void		put_pixel(t_img *im, int x, int y, int color);
void		set_hooks(t_mlx *m);
int			on_key(int key, t_mlx *m);
int			on_close(t_mlx *m);

/* raycaster */
void		raycast_render(t_mlx *m);

/* controls */
int			handle_key(t_mlx *m, int key);

#endif
