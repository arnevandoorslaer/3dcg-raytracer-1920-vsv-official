#include "math/transformation3d.h"
#include "math/transformation-matrices.h"

using namespace math;


Transformation3D math::transformations::translation(const Vector3D& v)
{
    Matrix4x4 tm = transformation_matrices::translation(v);
    Matrix4x4 itm = transformation_matrices::translation(-v);

    return Transformation3D(tm, itm);
}

Transformation3D math::transformations::scale(double sx, double sy, double sz) {
	Matrix4x4 tm = transformation_matrices::scaling(sx, sy, sz);
	Matrix4x4 itm = transformation_matrices::scaling(-sx, -sy, -sz);

	return Transformation3D(tm, itm);
}

Transformation3D transformations::rotate_around_x(const Angle a)
{
	const Matrix4x4 tm = transformation_matrices::rotation_around_x(a);
	const auto itm = transformation_matrices::rotation_around_x(-a);

	return Transformation3D(tm, itm);
}

Transformation3D transformations::rotate_around_y(Angle angle) {
	Matrix4x4 tm = transformation_matrices::rotation_around_y(angle);
	Matrix4x4 itm = transformation_matrices::rotation_around_y(-angle);

	return Transformation3D(tm, itm);
}

Transformation3D transformations::rotate_around_z(Angle angle) {
	Matrix4x4 tm = transformation_matrices::rotation_around_z(angle);
	Matrix4x4 itm = transformation_matrices::rotation_around_z(-angle);

	return Transformation3D(tm, itm);
}
