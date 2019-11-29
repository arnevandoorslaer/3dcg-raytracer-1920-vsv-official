#pragma once
#include "raytracers/ray-tracer-v5.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV6 : public RayTracerV5
			{
			public:
				TraceResult trace(const Scene&, 
					const math::Ray&, const double) const override;
				imaging::Color compute_refraction(const Scene&,
					const MaterialProperties&, const Hit&,
					const math::Ray&, const double) const;
			};
		}
		RayTracer v6();
	}
}