#include "../rtv1.h"

static void		draw_menu(t_color color, int pixel_start, t_image *image)
{
	int 	pixel_end;

	pixel_end = pixel_start + image->opp;
	while (pixel_start < pixel_end)
	{
		image->data[pixel_start] = color.b.b;
		color.u >>= 8;
		pixel_start++;
	}
}

void			init_menu(t_env *env)
{
	int 		x;
	int 		y;
	t_color		rgb_color;

	rgb_color.b.a = 0x00;
	rgb_color.b.r = 255;
	rgb_color.b.g = 255;
	rgb_color.b.b = 255;
	env->win_menu = mlx_new_window(env->mlx, 800, 1200, "Menu");
	mlx_key_hook(env->win_menu, &key_menu, env);
	env->img_menu = ft_new_image(env->mlx, 800, 1200, 1);
	x = 0;
	while(x < 800)
	{
		y = 0 ;
		while(y < 1200)
		{
			if (y <= 50 || x <= 50 || y >= 1150 || x >= 750)
				mlx_pixel_put(env->mlx, env->win_menu, x, y, 0xF0000ff);
			y++;
		}
		x++;
	}
}