#include "../rtv1.h"

static t_double3			get_color_from_texture(t_image *texture, double u, double v)
{
	t_double3		color;
	int				pixel_start;

	v = 1 - v;
	pixel_start = ((texture->width * (int)(v * texture->height) +
		(int)(u * texture->width)) * texture->opp);
	color.z = (double)((unsigned char)texture->data[pixel_start] / 255.0);
	color.y = (double)((unsigned char)texture->data[pixel_start + 1] / 255.0);
	color.x = (double)((unsigned char)texture->data[pixel_start + 2] / 255.0);
	return (color);
}

t_double3			get_texture(t_scene *scene, t_surface *surface, t_vector ray)
{
	t_double3	ve;
	t_double3	vn;
	t_double3	vp;
	double		phi;
	double		theta;
	double		u;
	double		v;

	ve = (t_double3){0, 1, 0};
	vn = (t_double3){0, 0, 1};
	vp = normalize(find_point(ray.pos, ray.dir, surface->distance));				//sphere
	phi = acos(-dot_product(vn, vp));
	theta = acos(dot_product(vp, ve) / sin(phi)) / (2 * PI);
	v = phi / PI;
	if (dot_product(cross_product(vn, ve), vp) > 0)
		u = theta;
	else
		u = 1 - theta;
	return(get_color_from_texture(scene->texture, u, v));
}
