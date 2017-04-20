#include "../rtv1.h"

t_light			*light_new(int type)
{
	t_light		*light;

	if ((light = (t_light*)malloc(sizeof(t_light))) == NULL)
		ft_error("Error : malloc() failed.\n");
	light->type = type;
	light->pos = (t_double3){0, 0, 0};
	light->dir = (t_double3){0, 0, 0};
	light->color = (t_double3){0, 0, 0};
	return (light);
}

void			light_add(t_light **first, t_light *new)
{
	new->next = *first;
	*first = new;
}

t_object		*object_new(int type)
{
	t_object	*object;

	if ((object = (t_object*)malloc(sizeof(t_object))) == NULL)
		ft_error("Error : malloc() failed.\n");
	object->type = type;
	object->pos = (t_double3){0, 0, 0};
	object->rotation = (t_double3){0, 0, 0};
	object->radius = 0;
	object->dcp_min = (t_double3){0, 0, 0};
	object->dcp_max = (t_double3){0, 0, 0};
	object->color = (t_double3){1, 1, 1};
	object->reflex = 0;
	object->transparency = 0;
	object->gloss = 0;
	object->refraction = 1.2;
	object->next = NULL;
	return (object);
}

void			object_add(t_object **first, t_object *new)
{
	new->next = *first;
	*first = new;
}

void			print_object(t_object **first, t_light **first_l)
{
	t_object	*tmp;
	t_light		*tmp_l;
	int			i;

	tmp = *first;
	tmp_l = *first_l;
	i = 0;
	while (tmp)
	{
		printf("OBJECT %d :\t", i++);
		if (tmp->type == SPHERE)
			printf("SPHERE\n");
		if (tmp->type == PLANE)
			printf("PLANE\n");
		if (tmp->type == CYLINDER)
			printf("CYLINDER\n");
		if (tmp->type == CONE)
			printf("CONE\n");
		printf("\tPOSITION :\t(%.2f, %.2f, %.2f)\n", tmp->pos.x, tmp->pos.y, tmp->pos.z);
		printf("\tROTATION :\t(%.2f, %.2f, %.2f)\n", tmp->rotation.x, tmp->rotation.y, tmp->rotation.z);
		printf("\tRADIUS :\t%.2f\n", tmp->radius);
		printf("\tCOLOR :\t\t(%.2f, %.2f, %.2f)\n", tmp->color.x, tmp->color.y, tmp->color.z);
		printf("\tREFLEXION :\t%.2f\n", tmp->reflex);
		printf("\tTRANSPARENCY :\t%.2f\n", tmp->transparency);
		printf("\tGLOSS :\t\t%.2f\n", tmp->gloss);
		printf("\tREFRACTION :\t%.2f\n\n", tmp->refraction);
		printf("\tDCP_MIN :\t(%.2f, %.2f, %.2f)\n", tmp->dcp_min.x, tmp->dcp_min.y, tmp->dcp_min.z);
		printf("\tDCP_MAX :\t(%.2f, %.2f, %.2f)\n", tmp->dcp_max.x, tmp->dcp_max.y, tmp->dcp_max.z);
		tmp = tmp->next;
	}
	i = 0;
	while (tmp_l)
	{
		printf("LIGHT %d :\t", i++);
		if (tmp_l->type == SPOTLIGHT)
			printf("SPOTLIGHT\n");
		printf("\tPOSITION :\t(%.2f, %.2f, %.2f)\n", tmp_l->pos.x, tmp_l->pos.y, tmp_l->pos.z);
		printf("\tROTATION :\t(%.2f, %.2f, %.2f)\n", tmp_l->dir.x, tmp_l->dir.y, tmp_l->dir.z);
		printf("\tCOLOR :\t\t(%.2f, %.2f, %.2f)\n", tmp_l->color.x, tmp_l->color.y, tmp_l->color.z);
		tmp_l = tmp_l->next;
	}
}
