#include "raytracers/ray-tracer-v4.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(
	const Scene& scene, const MaterialProperties& props, 
	const Hit& hit, const math::Ray& ray, LightRay& lightray) const
{
	auto inter = scene.root->find_all_hits(lightray.ray);
	for each (std::shared_ptr<Hit> hit in inter)
	{
		if (hit.get()->t >= 0 && hit.get()->t < 1)
		{
			return colors::black();
		}
	}
	return RayTracerV3::process_light_ray(scene,
		props, hit, ray, lightray);
}

raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}
