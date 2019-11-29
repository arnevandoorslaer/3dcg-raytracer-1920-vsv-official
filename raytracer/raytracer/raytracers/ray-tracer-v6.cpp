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
	const auto result = colors::black();

	if (props.transparency > 0)
	{
		const double n1 = 1;
		const auto n2 = props.refractive_index;

		auto i = (hit.position - ray.origin).normalized();
		const auto n = hit.normal;

		auto ox = (n1 / n2) * (i - i.dot(n) * n);
		const auto oy = (-1 * sqrt(1 - ox.dot(ox))) * n;
		const auto o = ox + oy;

		if (1 - ox.dot(ox) < 0)
		{
			return result;
		}

		const auto enter_vector_moved_slightly = hit.position + o * 0.0000001;
		const auto enter_ray = Ray(enter_vector_moved_slightly, o);

		Hit exit_hit;

		if (scene.root->find_first_positive_hit(enter_ray, &exit_hit))
		{
			auto exit_properties = exit_hit.material->at(exit_hit.local_position);
			if (!(exit_properties.transparency > 0)) {
				return trace(scene, enter_ray, weight * props.transparency).color * props.transparency;
			}
			auto exit_i = enter_ray.direction.normalized();
			auto exit_n = exit_hit.normal;
			auto exit_ox = (n2 / n1) * (exit_i - exit_i.dot(exit_n) * exit_n);

			const auto exit_oy = (-1 * sqrt(1 - exit_ox.dot(exit_ox))) * exit_n;
			const auto exit_o = exit_ox + exit_oy;

			if (1 - exit_ox.dot(exit_ox) < 0)
			{
				return result;
			}

			const auto exit_vector_moved_slightly = exit_hit.position + exit_o * 0.0000001;
			const auto exit_ray = Ray(exit_vector_moved_slightly, exit_o);
			return trace(scene, exit_ray, weight * exit_properties.transparency).color * exit_properties.transparency;
		}
	}

	return result;
}

raytracer::RayTracer raytracer::raytracers::v6()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}
