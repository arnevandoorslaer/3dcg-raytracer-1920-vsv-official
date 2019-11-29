#pragma once
#include "raytracers/ray-tracer-v3.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV4 : public RayTracerV3
			{
			public:
				imaging::Color process_light_ray(const Scene&,
					const MaterialProperties&, const Hit&,
					const math::Ray&, LightRay&) const override;
			};
		}
		RayTracer v4();
	}
}