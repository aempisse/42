#include "../rtv1.h"

static void		color_pixel_menu_image(t_color color, int pixel_start,
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

static void		draw_background(t_env *env, int x, int y)
{
	t_color		rgb_color;

	rgb_color.b.a = 0x00;
	rgb_color.b.r = 34;
	rgb_color.b.g = 45;
	rgb_color.b.b = 74;
	if (y <= 25 || x <= 25 || y >= 575 || x >= 475)
		color_pixel_menu_image(rgb_color, (800 * y + x) * env->menu->img->opp, env->menu->img);
	if ((x >= 150 && x <= 155) && y >= 100 && y < 150)
		color_pixel_menu_image(rgb_color, (800 * y + x) * env->menu->img->opp, env->menu->img);
	if ((x >= 345 && x <= 350) && y >= 100 && y < 150)
		color_pixel_menu_image(rgb_color, (800 * y + x) * env->menu->img->opp, env->menu->img);
	if ((x >= 150 && x <= 350) && y >= 100 && y < 105)
		color_pixel_menu_image(rgb_color, (800 * y + x) * env->menu->img->opp, env->menu->img);
	if ((x >= 150 && x <= 350) && y >= 150 && y < 155)
		color_pixel_menu_image(rgb_color, (800 * y + x) * env->menu->img->opp, env->menu->img);
}

void	render_menu(t_env *env)
{
	int 	x;
	int 	y;

	y = 0;
	while(y < 600)
	{
		x = 0;
		while(x < 500)
		{
			draw_background(env, x, y);
			x++;
		}
		y++;
	}
}