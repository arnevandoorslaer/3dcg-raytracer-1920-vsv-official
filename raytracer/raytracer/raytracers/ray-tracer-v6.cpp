#include "ray-tracer-v6.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(
	const Scene& scene, const math::Ray& ray, const double weight) const
{
	Hit hit;

	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		Color color = colors::black();
		if (weight >= 0.01)
		{
			Color hit_color = hit.material->at(hit.local_position).ambient;
			MaterialProperties props = hit.material->at(hit.local_position);
			color += hit_color;
			color += process_lights(scene, props, hit, ray);

			color += compute_reflection(scene, props, ray, hit, weight);
			color += compute_refraction(scene, props, hit, ray, weight);
		}

		unsigned group_id = hit.group_id;

		double t = hit.t;

		return TraceResult(color, group_id, ray, t);
	}
	else
	{
		return TraceResult::no_hit(ray);
	}
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_refraction(
	const Scene& scene, const MaterialProperties& props, 
	const Hit& hit,const math::Ray& ray, const double weight) const
{
	return colors::black();
}

raytracer::RayTracer raytracer::raytracers::v6()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}
