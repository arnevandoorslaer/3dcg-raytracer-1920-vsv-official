#include "raytracers/ray-tracer-v4.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(
	const Scene& scene, const MaterialProperties& props, 
	const Hit& hit, const math::Ray& ray, LightRay& lightray) const
{
	Hit shadowhit;
	scene.root->find_first_positive_hit(lightray.ray, &shadowhit);
	if (shadowhit.t >= 0 && shadowhit.t < 0.9999)
	{
		return colors::black();
	}
	return RayTracerV3::process_light_ray(scene,
		props, hit, ray, lightray);
}

raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}
