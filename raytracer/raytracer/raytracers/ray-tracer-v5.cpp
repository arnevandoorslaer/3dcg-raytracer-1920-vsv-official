#include "raytracers/ray-tracer-v5.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(
	const Scene& scene, const math::Ray& ray) const
{
	return trace(scene, ray, 1.0);
}

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(
	const Scene& scene, const math::Ray& ray, const double weight) const
{
	Hit hit;

	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		Color color = colors::black();
		if (weight >= 0.01)
		{
			Color hit_color = hit.material->at(hit.local_position).ambient;
			color += hit_color;
			color += process_lights(scene, hit.material->at(hit.local_position), hit, ray);
		
			color += compute_reflection(scene, hit.material->at(hit.local_position), ray,
				hit, weight);
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

imaging::Color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(
	const Scene& scene, const MaterialProperties& props, const math::Ray& ray, 
	const Hit& hit, const double weight) const
{
	if (props.reflectivity > 0) {
		auto reflected = ray.direction.reflect_by(hit.normal);
		math::Ray ray2 = math::Ray(
			hit.position+0.000001* reflected, reflected);
		return props.reflectivity * trace(scene, ray2, 
			weight*props.reflectivity).color;
	}
	else
	{
		return colors::black();
	}
}

raytracer::RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}
