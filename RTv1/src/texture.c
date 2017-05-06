#include "../rtv1.h"

static t_double3	get_color_from_texture(t_image *texture, double u, double v)
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

t_double3			planar_mapping(t_scene *scene, t_surface *surface, t_vector ray, t_object *object)
{
	double			u;
	double			v;
	t_double3		point;

	point = find_point(ray.pos, ray.dir, surface->distance);
	if (object->dcp)
	{
		u = (point.x - object->dcp_x.x) / (object->dcp_x.y - object->dcp_x.x);
		v = (point.y - object->dcp_y.x) / (object->dcp_y.y - object->dcp_y.x);
	}
	else
	{
		u = fmod(abs_double(point.x) ,(scene->texture->width / 100.0)) / (scene->texture->width / 100.0);
		v = fmod(abs_double(point.y) ,(scene->texture->height / 100.0)) / (scene->texture->height / 100.0);
	}
	return(get_color_from_texture(scene->texture, u, v));
}

t_double3			spherical_mapping(t_scene *scene, t_surface *surface, t_vector ray)
{
	t_double3		ve;
	t_double3		vn;
	t_double3		vp;
	double			phi;
	double			theta;
	double			u;
	double			v;

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

t_double3			cylindrical_mapping(t_scene *scene, t_surface *surface, t_vector ray, t_object *object)
{
	t_double3		ve;
	t_double3		vn;
	t_double3		vp;
	double			u;
	double			v;
	double			theta;

	ve = (t_double3){0, 1, 0};
	vn = (t_double3){0, 0, 1};
	vp = find_point(ray.pos, ray.dir, surface->distance);
	theta = acos(dot_product(ve, normalize((t_double3){vp.x, vp.y, 0}))) / (2 * PI);
	if (object->dcp)
		v = (vp.z - object->dcp_z.x) / (object->dcp_z.y - object->dcp_z.x);
	else
		v = fmod(abs_double(vp.z) ,(scene->texture->height / 100.0)) / (scene->texture->height / 100.0);
	if (dot_product(cross_product(vn, ve), vp) > 0)
		u = theta;
	else
		u = 1 - theta;
	return(get_color_from_texture(scene->texture, u, v));
}
