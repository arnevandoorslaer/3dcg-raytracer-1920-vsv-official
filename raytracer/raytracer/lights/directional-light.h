#pragma once

#include "math/vector.h"
#include "imaging/color.h"
#include "lights/point-light.h"
#include "lights/light-source.h"
#include <memory>

namespace raytracer
{
	namespace lights
	{
		LightSource directionalLight(const math::Vector3D& direction, const imaging::Color& color);
	}

}