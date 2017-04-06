#include "../rtv1.h"

t_double3		rotation_x(t_double3 point, double angle)
{
	t_double3	point_t;

	if (angle == 0)
		return (point);
	angle = angle * (PI / 180.0);
	point_t.x = point.x;
	point_t.y = point.y * cos(angle) - point.z * sin(angle);
	point_t.z = point.y * sin(angle) + point.z * cos(angle);
	return (point_t);
}

t_double3		rotation_y(t_double3 point, double angle)
{
	t_double3	point_t;

	if (angle == 0)
		return (point);
	angle = angle * (PI / 180.0);
	point_t.x = point.x * cos(angle) + point.z * sin(angle);
	point_t.y = point.y;
	point_t.z = -point.x * sin(angle) + point.z * cos(angle);
	return (point_t);
}

t_double3		rotation_z(t_double3 point, double angle)
{
	t_double3	point_t;

	if (angle == 0)
		return (point);
	angle = angle * (PI / 180.0);
	point_t.x = point.x * cos(angle) - point.y * sin(angle);
	point_t.y = point.x * sin(angle) + point.y * cos(angle);
	point_t.z = point.z;
	return (point_t);
}