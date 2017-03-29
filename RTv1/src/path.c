#include "../rtv1.h"

t_double3			reflect(t_double3 incidence, t_double3 normal)
{
	t_double3		reflect;

	reflect.x = incidence.x - 2 * dot_product(incidence, normal) * normal.x;
	reflect.y = incidence.y - 2 * dot_product(incidence, normal) * normal.y;
	reflect.z = incidence.z - 2 * dot_product(incidence, normal) * normal.z;
	return (reflect);
}

t_double3			refract(t_double3 incidence, t_double3 normal, double ior)
{
	t_double3		refract;
	double			cosi;
	double			etai;
	double			etat;
	double			eta;
	double			k;

	cosi = max_double(-1.0, min_double(1.0, dot_product(incidence, normal)));
	etai = 1;
	etat = ior;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		swap(&etai, &etat);
		normal = vec_minus_vec((t_double3){0, 0, 0}, normal);
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	refract = k < 0 ? (t_double3){0, 0, 0} : (t_double3){
	eta * incidence.x + (eta * cosi - sqrt(k)) * normal.x,
	eta * incidence.y + (eta * cosi - sqrt(k)) * normal.y,
	eta * incidence.z + (eta * cosi - sqrt(k)) * normal.z};
	return (refract);
}

void				fresnel(t_double3 incidence, t_double3 normal, double ior, double *kr)
{
	double			cosi;
	double			etai;
	double			etat;
	double			sint;
	double			k;
	double			cost;
	double			rs;
	double			rp;

	cosi = max_double(-1.0, min_double(1.0, dot_product(incidence, normal)));
	etai = 1;
	etat = ior;
	if (cosi > 0)
		swap(&etai, &etat);
	sint = etai / etat * sqrt(max_double(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*kr = 1;
	else
	{
		cost = sqrt(max_double(0.0, 1 - sint * sint));
		cosi = cosi > 0 ? cosi : -cosi;
		rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*kr = (rs * rs + rp * rp) / 2.0;
	}
}