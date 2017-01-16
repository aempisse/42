#include "../rtv1.h"

void			ft_put_image(t_image *img, int pos, t_color color)
{
	int			to;

	to = pos + img->opp;
	while (pos < to)
	{
		img->data[pos] = color.b.b;
		color.u >>= 8;
		pos++;
	}
}

t_double3		normalize(t_double3 vec)
{
	t_double3	normalized;
	double		square;
	double		norm;

	if ((square = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)) == 0)
		return ((t_double3){0, 0, 0});
	norm = 1 / square;
	normalized.x = vec.x * norm;
	normalized.y = vec.y * norm;
	normalized.z = vec.z * norm;
	return (normalized);
}

double			dot_product(t_double3 vec1, t_double3 vec2)
{
	double		product;

	product = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (product);
}

int				intersect(t_env *env, t_double3 dir, t_sphere *sphere)
{
	t_double3	center;
	double		a;
	double		b;
	double		c;
	double		discr;

	center.x = env->camera.pos.x - sphere->pos.x;
	center.y = env->camera.pos.y - sphere->pos.y;
	center.z = env->camera.pos.z - sphere->pos.z;
	a = dot_product(dir, dir);
	b = 2 * dot_product(dir, center);
	c = dot_product(center, center) - sphere->radius * sphere->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	return (1);
}

void			raytracer(t_env *env, int x, int y)
{
	/*
	** On calcule la direction du rayon. On a besoin de connaitre les coordonnées
	** dans l'espace réél du point (pixel_camera) qui correspond au milieu du pixel du plan
	** de la caméra. Ces coordonnées dépendent des variables x et y passées en argument de
	** cette fonction.
	**
	** L'espace réél est défini par trois vecteurs unitaires de base qui représentent les trois
	** directions d'un espace à 3 dimensions : X, Y et Z. Ils sont unitaires car leur longueur
	** est exactement de 1 unité et représentent une base car, pour faire très simple, ils sont
	** orthogonaux entre eux. Tu peux approfondir sur l'algèbre linéaire si t'as la motive.
	** N'importe quel point de cet espace peut donc être exprimé par trois scalaires (ou coefficients)
	** qui sont en fait des nombres rééls qui vont multiplier les vecteurs unitaires de base.
	** 
	** Par exemple, lorsqu'on dit qu'un point se trouve en (-3, 7, 0.42), pour le trouver à partir
	** de l'origine de l'espace il faut se déplacer de -3 dans la direction de X, puis de 7 dans la
	** direction de Y, puis de 0.42 dans la direction de Z.
	** Pour calculer les coordonnées dans l'espace réél du point pixel_camera il faut transformer 
	** x et y pour les exprimer sous la forme de trois scalaires.
	**
	** Le point d'origine de la caméra (le point d'où partent les rayons) se trouve en (0, 0, 0).
	** Le plan se situe à -1 dans la direction de Z. Pour l'instant prenons le cas simplifié où le
	** plan de la caméra s'étend de 1 à -1 dans la direction de X et de 1 à -1 dans la direction de Y.
	** Ce plan est donc un carré de 2 unités de côté, situé à 1 unité du point d'origine.
	**
	** La coordonnée en X :
	**		- on a x							(compris entre 0 et WIDTH)
	**		- on fait le ratio entre x et WIDTH	(compris entre 0 et 1)
	**		- on muliplie ce ratio par 2		(compris entre 0 et 2)
	**		- on lui soustrait 1				(compris entre -1 et 1)
	**
	** La coordonnée en Y :
	**		- on a y							(compris entre 0 et HEIGHT)
	**		- on fait le ratio entre y et HEIGHT(compris entre 0 et 1)
	**		- on muliplie ce ratio par 2		(compris entre 0 et 2)
	**		- on le soustrait à 1				(compris entre -1 et 1)
	**
	** Pour la coordonnée en Z c'est facile, c'est -1 (cf le paragraphe au dessus).
	** La petite différence entre les calculs pour les coordonnées en X et en Y vient du fait que
	** y varie de 0 quand il est tout en haut à HEIGHT quand il est tout en bas, alors que le vecteur
	** Y va du bas vers le haut dans un repère classique.
	**
	** Ensuite on va utiliser la variable aspect_ratio pour compenser la déformation du pixel dans le
	** cas à le plan de la caméra n'est pas carré (WIDTH != HEIGHT).
	** Il reste encore une correction à faire. En fait dans le cas simplifié dont je parlais au dessus
	** l'angle de vue qu'on obtient est de 90° (plan de 2 unités de côté, situé à 1 unité de l'origine).
	** Pour obtenir l'angle qu'on veut, on corrige les valeurs avec la variable scale. Pour le calcul je 
	** te montrerai avec un schéma ce sera plus simple.
	**
	** On a désormais les coordonnées dans l'espace réél du point au milieu du pixel (x, y). Le "+ 0.5"
	** dans les calculs sert à viser le milieu.
	** 
	** Il ne reste plus qu'à normaliser le vecteur de direction du rayon. Ainsi le vecteur aura une
	** longueur d'exactement une unité comme les vecteurs unitaires de l'espace.
	**
	** je vais me coucher, la suite plus tard !
	** essaye déjà de bien comprendre tout ça ce sera un très bon début
	*/
	t_double3	pixel_camera;
	double		aspect_ratio;
	double		scale;
	t_sphere	*tmp;
	t_color		color;
	int			i;

	aspect_ratio = WIDTH / (double)HEIGHT;
	scale = tan((env->fov * 0.5) * PI / 180.0);
	pixel_camera.x = (2 * ((x + 0.5) / (double)WIDTH) - 1) * aspect_ratio * scale;
	pixel_camera.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
	pixel_camera.z = -1;
	pixel_camera = normalize(pixel_camera);
	i = -1;
	color.u = 0x00000000;
	while (++i < env->sphere->length)
	{
		tmp = AG(t_sphere*, env->sphere, i);
		if (intersect(env, pixel_camera, tmp) == 1)
			color.u = 0x00FFFFFF;
	}
	ft_put_image(env->img, (WIDTH * y + x) * env->img->opp, color);
}

void			render(t_env *env)
{
	/*
	** On parcourt les pixels du plan de la caméra (l'écran) avec x et y.
	*/
	int			x;
	int			y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			raytracer(env, x, y);
	}
}