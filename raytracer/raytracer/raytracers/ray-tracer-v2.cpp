#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV2::trace(const Scene& scene, const Ray& ray) const
{
	Hit hit;

	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		Color color = colors::black();
		Color hit_color = hit.material->at(hit.local_position).ambient;
		color += hit_color;
		color += process_lights(scene, hit.material->at(hit.local_position), hit, ray);
		
		unsigned group_id = hit.group_id;

		double t = hit.t;

		return TraceResult(color, group_id, ray, t);
	}
	else
	{
		return TraceResult::no_hit(ray);
	}
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_lights(
	const Scene& scene, const MaterialProperties& props,
	const Hit& hit, const math::Ray& ray) const
{
	Color result = colors::black();
	for each (LightSource source in scene.light_sources)
	{
		result += process_light_source(scene, props, 
			hit, ray, source);
	}
	return result;
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene& scene, const MaterialProperties& props,
	const Hit& hit, const math::Ray& ray, LightSource source) const
{
	Color result = colors::black();
	for each (LightRay light in source->lightrays_to(hit.position))
	{
		result += process_light_ray(scene, props, hit, ray, light);
	}
	return result;
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& props,
	const Hit& hit, const math::Ray& ray, LightRay& lightray) const
{
	Color result = colors::black();
	result += compute_diffuse(props, hit, ray, lightray);
	return result;
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& props,
	const Hit& hit, const math::Ray& ray, LightRay& lightray) const
{
	Color Cl = lightray.color;
	math::Point3D L = lightray.ray.origin;
	math::Point3D P = hit.position;
	Color Cs = hit.material->at(hit.local_position).diffuse;
	math::Vector3D vectorN = hit.normal;

	auto cos = (L - P).normalized().dot(vectorN);

	if (cos > 0)
	{
		return Cl * Cs * cos;
	}
	else
	{
		return colors::black();
	}
}
raytracer::RayTracer raytracer::raytracers::v2()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}