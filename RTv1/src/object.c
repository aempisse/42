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

void			neg_obj_add(t_negobj **first, t_negobj *new)
{
	new->next = *first;
	*first = new;
}

t_negobj		*neg_obj_new()
{
	t_negobj	*object;

	if ((object = (t_negobj*)malloc(sizeof(t_negobj))) == NULL)
		ft_error("Error : malloc() failed.\n");
	object->pos = (t_double3){0, 0, 0};
	object->rotation = (t_double3){0, 0, 0};
	object->radius = 0;
	return (object);
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
	object->dcp_x = (t_double2){0, 0};
	object->dcp_y = (t_double2){0, 0};
	object->dcp_z = (t_double2){0, 0};
	object->color = (t_double3){1, 1, 1};
	object->reflex = 0;
	object->transparency = 0;
	object->gloss = 0;
	object->refraction = 1.2;
	object->next = NULL;
	object->dcp = 0;
	return (object);
}

void			object_add(t_object **first, t_object *new)
{
	new->next = *first;
	*first = new;
}

void			print_object(t_object **first, t_light **first_l, t_negobj **first_n)
{
	t_object	*tmp;
	t_light		*tmp_l;
	t_negobj	*tmp_n;
	int			i;

	tmp = *first;
	tmp_l = *first_l;
	tmp_n = *first_n;
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
		printf("\tDCP_X :\t(%.2f, %.2f)\n", tmp->dcp_x.x, tmp->dcp_x.y);
		printf("\tDCP_Y :\t(%.2f, %.2f)\n", tmp->dcp_y.x, tmp->dcp_y.y);
		printf("\tDCP_Z :\t(%.2f, %.2f)\n", tmp->dcp_z.x, tmp->dcp_z.y);
		printf("\tDCP_BOOL :\t%i\n", tmp->dcp);
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
	i = 0;
	while (tmp_n)
	{
		printf("NEG_OBJ %d :\n", i++);		
		printf("\tPOSITION :\t(%.2f, %.2f, %.2f)\n", tmp_n->pos.x, tmp_n->pos.y, tmp_n->pos.z);
		printf("\tROTATION :\t(%.2f, %.2f, %.2f)\n", tmp_n->rotation.x, tmp_n->rotation.y, tmp_n->rotation.z);
		printf("\tRADIUS :\t%.2f\n", tmp_n->radius);
		tmp_n = tmp_n->next;
	}
}
