#pragma once
#include "primitives/primitive.h"

using namespace math;

namespace raytracer
{
	namespace primitives
	{
		Primitive mesh(const std::string& file);
	}
}