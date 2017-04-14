#include "../rtv1.h"

t_light			*light_new(void)
{
	t_light		*light;

	if ((light = (t_light*)malloc(sizeof(t_light))) == NULL)
		ft_error("Error : malloc() failed.\n");
	light->position = (t_double3){0, 0, 0};
	light->direction = (t_double3){0, 0, 0};
	light->color = (t_double3){0, 0, 0};
	return (light);
}

void			light_add(t_light **first, t_light *new)
{
	new->next = *first;
	*first = new;
}

t_object		*object_new(void)
{
	t_object	*object;

	if ((object = (t_object*)malloc(sizeof(t_object))) == NULL)
		ft_error("Error : malloc() failed.\n");
	object->type = 0;
	object->position = (t_double3){0, 0, 0};
	object->rotation = (t_double3){0, 0, 0};
	object->radius = 0;
	object->color = (t_double3){0, 0, 0};
	object->reflexion = 0;
	object->transparency = 0;
	object->gloss = 0;
	object->refraction = 0;
	object->next = NULL;
	return (object);
}

void			object_add(t_object **first, t_object *new)
{
	new->next = *first;
	*first = new;
}

void			print_object(t_object **first)
{
	t_object	*tmp;
	int			i;

	tmp = *first;
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
		printf("\tPOSITION :\t(%.2f, %.2f, %.2f)\n", tmp->position.x, tmp->position.y, tmp->position.z);
		printf("\tROTATION :\t(%.2f, %.2f, %.2f)\n", tmp->rotation.x, tmp->rotation.y, tmp->rotation.z);
		printf("\tRADIUS :\t%.2f\n", tmp->radius);
		printf("\tCOLOR :\t\t(%.2f, %.2f, %.2f)\n", tmp->color.x, tmp->color.y, tmp->color.z);
		printf("\tREFLEXION :\t%.2f\n", tmp->reflexion);
		printf("\tTRANSPARENCY :\t%.2f\n", tmp->transparency);
		printf("\tGLOSS :\t\t%.2f\n", tmp->gloss);
		printf("\tREFRACTION :\t%.2f\n\n", tmp->refraction);
		tmp = tmp->next;	
	}
}