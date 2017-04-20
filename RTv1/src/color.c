#include "../rtv1.h"

static void		color_pixel_image(t_color color, int pixel_start,
	t_image *image)
{
	int			pixel_end;

	pixel_end = pixel_start + image->opp;
	while (pixel_start < pixel_end)
	{
		image->data[pixel_start] = color.b.b;
		color.u >>= 8;
		pixel_start++;
	}
}

void			color_standard(t_env *env, t_double3 color, int x, int y)
{
	t_color		rgb_color;

	rgb_color.b.a = 0x00;
	rgb_color.b.r = 255 * max_double(0, min_double(1, color.x));
	rgb_color.b.g = 255 * max_double(0, min_double(1, color.y));
	rgb_color.b.b = 255 * max_double(0, min_double(1, color.z));
	color_pixel_image(rgb_color, (WIDTH * y + x) * env->img->opp, env->img);
	mlx_pixel_put(env->mlx, env->win_scene, x, y, 0xFFFFFFFF);
}
