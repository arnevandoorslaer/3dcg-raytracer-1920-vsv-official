#include "raytracers/ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(
	const Scene& scene, const MaterialProperties& props,
	const Hit& hit, const math::Ray& ray, LightRay& lightray) const
{
	Color result = RayTracerV2::process_light_ray(
	scene, props, hit, ray, lightray);
	result += compute_specular(props, hit, ray, lightray);
	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(
	const MaterialProperties& props, const Hit& hit, 
	const Ray& ray, const LightRay& lightray) const
{
	if (props.specular == colors::black())
	{
		return colors::black();
	}
	else
	{
		Color cl = lightray.color;
		math::Point3D L = lightray.ray.origin;
		math::Point3D P = hit.position;
		Color cp = props.specular;
		math::Point3D E = ray.origin;
		double e = props.specular_exponent;

		auto i = (P - L).normalized();
		auto r = i.reflect_by(hit.normal);
		auto v = (E - P).normalized();
		auto cos = v.dot(r);
		if (cos > 0)
		{
			return cl * cp * pow(cos, e);
		}
		else
		{
			return colors::black();
		}
	}
}
raytracer::RayTracer raytracer::raytracers::v3()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}
