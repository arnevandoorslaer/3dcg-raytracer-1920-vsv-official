#pragma once

#include "primitives/primitive.h"
#include "math/transformation3d.h"
#include <memory>
using namespace math;

namespace raytracer
{
    namespace primitives
    {
        Primitive transform(const math::Transformation3D&, Primitive);
        Primitive translate(const math::Vector3D&, Primitive);
		Primitive scale(double sx, double sy, double sz, Primitive transformee);
		Primitive rotate_around_x(Angle, Primitive);
		Primitive rotate_around_y(const Angle angle, Primitive transformee);
		Primitive rotate_around_z(const Angle angle, Primitive transformee);
    }
}