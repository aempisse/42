#include "../rtv1.h"

static void		init_cone_obj(t_env *env)
{
	t_cone		*cone;

	cone = (t_cone*)malloc(sizeof(t_cone));
	cone->pos.x = 0;
	cone->pos.y = 0;
	cone->pos.z = 0;
	cone->normal.x = 0;
	cone->normal.y = 0;
	cone->normal.z = 0;
	cone->aperture = 0;
	cone->color.x = 0;
	cone->color.y = 0;
	cone->color.z = 0;
	cone->ior = 0;
	cone->material = 0;
	env->i_cone++;
	ft_array_add(env->objects->cone, cone);
}

static void		init_cylinder_obj(t_env *env)
{
	t_cylinder		*cylinder;

	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	cylinder->pos.x = 0;
	cylinder->pos.y = 0;
	cylinder->pos.z = 0;
	cylinder->normal.x = 0;
	cylinder->normal.y = 0;
	cylinder->normal.z = 0;
	cylinder->radius = 0;
	cylinder->color.x = 0;
	cylinder->color.y = 0;
	cylinder->color.z = 0;
	cylinder->ior = 0;
	cylinder->material = 0;
	env->i_cylinder++;
	ft_array_add(env->objects->cylinder, cylinder);
}

static void		init_plane_obj(t_env *env)
{
	t_plane		*plane;

	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->pos.x = 0;
	plane->pos.y = 0;
	plane->pos.z = 0;
	plane->normal.x = 0;
	plane->normal.y = 0;
	plane->normal.z = 0;
	plane->color.x = 0;
	plane->color.y = 0;
	plane->color.z = 0;
	plane->ior = 0;
	plane->material = 0;
	env->i_plane++;
	ft_array_add(env->objects->planes, plane);
}

static void		init_sphere_obj(t_env *env)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->pos.x = 0;
	sphere->pos.y = 0;
	sphere->pos.z = 0;
	sphere->radius = 0;
	sphere->color.x = 0;
	sphere->color.y = 0;
	sphere->color.z = 0;
	sphere->ior = 0;
	sphere->material = 0;
	env->i_sphere++;
	ft_array_add(env->objects->spheres, sphere);
}

void			init_object(t_env *env, char *obj)
{
	if (ft_strcmp(obj, "Sphere") == 0)
		init_sphere_obj(env);
	else if (ft_strcmp(obj, "Plane") == 0)
		init_plane_obj(env);
	else if (ft_strcmp(obj, "Cylinder") == 0)
		init_cylinder_obj(env);
	else if (ft_strcmp(obj, "Cone") == 0)
		init_cone_obj(env);
	else if (ft_strcmp(obj, "Light") == 0)
		init_light_obj(env);
}
