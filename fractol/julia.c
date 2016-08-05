#include "fractol.h"

int				ft_julia_loop(t_env *env, long int x, long int y)
{
	const t_complex c = (t_complex){x / env->zoom, y / env->zoom};
	t_complex		z;
	t_complex		sq;
	int				loop;
	long double		tmp;

	z = (t_complex){0, 0};
	sq = (t_complex){0, 0};
	loop = -1;
	while (((sq.r + sq.i) < 4) && ++loop < env->loop)
	{
		sq.r = z.r * z.r;
		sq.i = z.i * z.i;
		tmp = z.r;
		z.r = sq.r - sq.i + c.r;
		z.i = 2 * tmp * z.i + c.i;
	}
	return (loop);
}

void			ft_julia(t_env *env)
{
	t_lpt		pt;
	t_lpt		max;

	max = (t_lpt){WIDTH + env->offset.x, HEIGHT + env->offset.y};
	pt.y = env->offset.y;
	while (pt.y++ < max.y)
	{
		pt.x = env->offset.x;
		while (pt.x++ < max.x)
		{
			ft_put_image(env->img, (env->img->width * (pt.y - env->offset.y) + 
				(pt.x - env->offset.x)) * env->img->opp, 
				env->color(ft_julia_loop(env, pt.x, pt.y), env->loop));
		}
	}
}
