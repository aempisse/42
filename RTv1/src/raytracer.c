#include "../rtv1.h"

void			color_pixel_image(t_color color, int pixel_start, t_image *image)
{
	/*
	** On donne une couleur à un pixel avec color, pixel_start et image passés en argument.
	*/
	int			pixel_end;

	pixel_end = pixel_start + image->opp;
	while (pixel_start < pixel_end)
	{
		image->data[pixel_start] = color.b.b;
		color.u >>= 8;
		pixel_start++;
	}
}

void			swap(double *t0, double *t1)
{
	double tmp;

	tmp = *t0;
	*t0 = *t1;
	*t1 = tmp;
}

t_double3		normalize(t_double3 vec)
{
	/*
	** On normalise le vecteur vec passé en argument.
	*/
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
	/*
	** On calcule le produit scalaire des vecteurs vec1 et vec2 passés en argument.
	*/
	double		product;

	product = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (product);
}

void			distance_to_color(t_env *env, int x, int y, double distance)
{
	t_color		color;

	if (distance == -1)
		color.u = 0xFFF4F4F4;
	else
	{
		color.b.r = 0x00;
		color.b.g = (unsigned char)(((int)distance % 255));
		color.b.b = (unsigned char)(255 - ((int)distance % 255));
	}
	color_pixel_image(color, (WIDTH * y + x) * env->img->opp, env->img);
}

int 			intersect_plane(t_env *env, t_double3 dir, t_plane *plane, double *distance)
{
	double 		denom;
	t_double3	normal_plane;
	t_double3	center;

	center.x = env->camera.pos.x - plane->pos.x;
	center.y = env->camera.pos.y - plane->pos.y;
	center.z = env->camera.pos.z - plane->pos.z;
	normal_plane = normalize(plane->pos);
	denom = dot_product(dir, normal_plane);
	if (denom > 0.00001)
		*distance = dot_product(center, normal_plane) / denom;
	else
		return (0);
	return (1);
}

int				intersect(t_env *env, t_double3 dir, t_sphere *sphere, double *distance)
{
	/*
	** On détermine si il y a une intersection entre dir et sphere passés en argument.
	**
	** On injecte la forme paramétrique du vecteur du rayon :
	** 	O + D * t
	** 				O : point origine du rayon
	**				D : vecteur unitaire de direction du rayon
	**				t : scalaire qui représente la distance entre l'origine et l'intersection
	**	
	** à la place de P dans l'équation de la sphère :
	** 	(P - C)² - R² = 0
	**				P : point dans l'espace réél
	**				C : point du centre de la sphère
	**				R : rayon de la sphère
	** Un point P se trouve sur le bord de la sphère si l'équation se vérifie.
	**
	** Après simplification on obtient le polynôme de second degré :
	**	D² * t² + 2 * D * (O - C) * t + (O - C)² - R² = 0
	** Ici la variable est t. On obtient les éventuels points d'intersection du rayon avec la sphère
	** en calculant les racines du polynôme, c'est à dire les valeurs de t pour lesquelles l'équation
	** est nulle.
	**
	** Le polynôme est de la forme A * t² + B * t + C = 0
	** 		 		A = D²
	**				B = 2 * D * (O - C)
	**				C = (O - C)² - R²
	** Pour calculer le produit de deux vecteurs, comme D * (O - C) ou D², on fait un produit scalaire.
	**
	** On calcule le discriminant du polynôme : Δ = B² - 4 * A * C
	** 				Δ > 0 : Le polynôme a deux racines
	**				Δ = 0 : Le polynôme a une racine
	**				Δ < 0 : Le polynome n'a pas de racines
	** La version actuelle du raytracer détermine juste si le rayon touche une sphère ou pas, et si oui
	** affiche le pixel en blanc. Si Δ < 0 il n'y a pas d'intersection, sinon il y en a au moins une.
	*/
	t_double3	center;
	double		a;
	double		b;
	double		c;
	double		discr;
	double		t0;
	double		t1;
	double		tmp;

	center.x = env->camera.pos.x - sphere->pos.x;
	center.y = env->camera.pos.y - sphere->pos.y;
	center.z = env->camera.pos.z - sphere->pos.z;
	a = dot_product(dir, dir);
	b = 2 * dot_product(dir, center);
	c = dot_product(center, center) - sphere->radius * sphere->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	else
	{
		t0 = (- b - sqrt(discr)) / (2 * a);
		t1 = (- b + sqrt(discr)) / (2 * a);
		if (t0 > t1)
			swap(&t0, &t1);
		if (t0 < 0)
		{
			t0 = t1;
			if (t0 < 0)
				return (0);
		}
		*distance = t0;
	}
	return (1);
}

void			raytracer(t_env *env, int x, int y)
{
	/*
	** On calcule la direction du vecteur entre l'origine et le pixel (x, y) passé en argument.
	**
	** On a besoin de connaitre les coordonnées dans l'espace réél du point (pixel_camera)
	** qui correspond au milieu du pixel du plan de la caméra.
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
	** On peut donc exprimer sa position par l'expression : -3 * X + 7 * Y + 0.42 * Z
	** On a trois scalaires qui multiplient trois vecteurs unitaires.
	** Pour calculer les coordonnées dans l'espace réél du point pixel_camera il faut transformer 
	** x et y pour les exprimer sous la forme de trois scalaires.
	**
	** Le point d'origine de la caméra (le point d'où partent les rayons) se trouve en (0, 0, 0).
	** Le plan se situe à -1 dans la direction de Z. Pour l'instant prenons le cas simplifié où le
	** plan de la caméra s'étend de 1 à -1 dans la direction de X et de 1 à -1 dans la direction de Y.
	** Ce plan est donc un carré de 2 unités de côté, situé à 1 unité du point d'origine.
	**
	** La coordonnée en X :
	**		- on a x							(compris entre 0 et WIDTH)		<- de gauche à droite
	**		- on fait le ratio entre x et WIDTH	(compris entre 0 et 1)
	**		- on muliplie ce ratio par 2		(compris entre 0 et 2)
	**		- on lui soustrait 1				(compris entre -1 et 1)			<- de gauche à droite
	**
	** La coordonnée en Y :
	**		- on a y							(compris entre 0 et HEIGHT)		<- de haut en bas
	**		- on fait le ratio entre y et HEIGHT(compris entre 0 et 1)
	**		- on muliplie ce ratio par 2		(compris entre 0 et 2)
	**		- on le soustrait à 1				(compris entre -1 et 1)			<- de bas en haut
	**
	** Pour la coordonnée en Z c'est facile, c'est -1 (cf le paragraphe au dessus).
	** La petite différence entre les calculs pour les coordonnées en X et en Y vient du fait que
	** y varie de 0 quand il est tout en haut à HEIGHT quand il est tout en bas, alors que le vecteur
	** Y va du bas vers le haut dans un repère classique.
	** Le "+ 0.5" dans les calculs sert à viser le milieu du pixel.
	**
	** Ensuite on va utiliser la variable aspect_ratio pour compenser la déformation du pixel dans le
	** cas à le plan de la caméra n'est pas carré (WIDTH ≠ HEIGHT).
	** Il reste encore une correction à faire. En fait dans le cas simplifié dont je parlais au dessus
	** l'angle de vue qu'on obtient est de 90° (plan de 2 unités de côté, situé à 1 unité de l'origine).
	** Pour obtenir l'angle qu'on veut, on corrige les valeurs avec la variable scale. Pour le calcul je 
	** te montrerai avec un schéma ce sera plus simple.
	**
	** On a désormais les coordonnées dans l'espace réél du point pixel_camera au milieu du pixel (x, y).
	** La longueur du vecteur de direction tel qu'il est représenté par les trois scalaires qu'on a
	** trouvé est égale à la distance entre le point d'origine et le milieu du pixel.
	** 
	** Il ne reste plus qu'à normaliser le vecteur de direction du rayon. Ainsi le vecteur aura une
	** longueur d'exactement une unité comme les vecteurs unitaires de l'espace. Comme ça on pourra
	** exprimer n'importe quel point dans la direction du vecteur par un scalaire qui multiplie ce
	** vecteur unitaire.
	**
	** Si on garde le vecteur de direction tel quel, par exemple si il fait 1.27 unités de longueur
	** et que la sphère se trouve à 5.34 dans cette direction, le scalaire qui représentera la distance
	** du point de contact avec la sphère sera 5.34 / 1.27 = 4.20472440945
	** Si on se sert d'un vecteur unitaire, le scalaire sera 5.34 / 1 = 5.34
	** 
	** Et voilà c'est à peu près tout pour l'instant, ensuite on boucle à travers les sphères et on teste
	** pour chacune d'entre elles si le rayon les intersecte.
	** Si il y a intersection on affiche le pixel en blanc.
	*/
	t_double3	pixel_camera;
	double		aspect_ratio;
	double		scale;
	t_sphere	*sphere;
	t_plane		*plane;
	double		distance;
	double		nearest;
	int			i;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan(((env->fov * 0.5) * PI) / 180.0);
	pixel_camera.x = (2 * ((x + 0.5) / (double)WIDTH) - 1) * aspect_ratio * scale;
	pixel_camera.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
	pixel_camera.z = -1;
	pixel_camera = normalize(pixel_camera);
	nearest = -1;
	i = -1;
	while (++i < env->sphere->length)
	{
		sphere = AG(t_sphere*, env->sphere, i);
		if (intersect(env, pixel_camera, sphere, &distance))
			if (nearest == -1 || nearest > distance)
				nearest = distance;
	}
	i = -1;
	while (++i < env->plane->length)
	{
		plane = AG(t_plane*, env->plane, i);
		if (intersect_plane(env, pixel_camera, plane, &distance))
			if (nearest == -1 || nearest > distance)
				nearest = distance;
	}
	distance_to_color(env, x, y, nearest);
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