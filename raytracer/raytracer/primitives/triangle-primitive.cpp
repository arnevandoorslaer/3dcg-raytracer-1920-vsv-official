#include "primitives/triangle-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		const Point3D p1, p2 ,p3;
		Vector3D normal;

		TriangleImplementation(const Point3D& p1, 
			const Point3D& p2, const Point3D& p3) : p1(p1), p2(p2), p3(p3)
		{
			// compute the normal vector on the plane
			this->normal = (p2 - p1).cross(p3 - p1).normalized();
		}

		math::Box bounding_box() const override
		{
			auto x_min = std::min({ p1.x(), p2.x(), p3.x() });
			auto y_min = std::min({ p1.y(), p2.y(), p3.y() });
			auto z_min = std::min({ p1.z(), p2.z(), p3.z() });

			auto x_max = std::max({ p1.x(), p2.x(), p3.x() });
			auto y_max = std::max({ p1.y(), p2.y(), p3.y() });
			auto z_max = std::max({ p1.z(), p2.z(), p3.z() });

			return Box(
				interval(x_min, x_max),
				interval(y_min, y_max),
				interval(z_min, z_max)
			);
		}

		void initialize_hit(Hit* hit, const Ray& ray, double t) const
		{
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = normal;
		};

		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			// lijstje van de hits
			std::vector<std::shared_ptr<Hit>> hits;
			// t berekenen
			double t = (p1 - ray.origin).dot(normal);
			t = t / ray.direction.dot(normal);
			// hit positie
			Point3D H = ray.origin + (ray.direction * t);
			// hit rechts van p1 en p2 ?
			if ((p2 - p1).cross(H - p1).dot(normal) < 0)
			{
				return hits;
			}
			// hit rechts van p2 en p3 ?
			if ((p3 - p2).cross(H - p2).dot(normal) < 0)
			{
				return hits;
			}
			// hit rechts van p3 en p1 ?
			if ((p1 - p3).cross(H - p3).dot(normal) < 0)
			{
				return hits;
			}

			auto hit = std::make_shared<Hit>();
			initialize_hit(hit.get(), ray, t);
			hits.push_back(hit);

			return hits;
		}

		bool find_first_positive_hit(const Ray& ray, Hit* output_hit) const override
		{
			double t = (p1 - ray.origin).dot(normal) / ray.direction.dot(normal);
			if (t < 0 || t >= output_hit->t)
			{
				return false;
			}
			Point3D H = ray.origin + (ray.direction * t);

			// hit rechts van p1 en p2 ?
			if ((p2 - p1).cross(H - p1).dot(normal) < 0)
			{
				return false;
			}
			// hit rechts van p2 en p3 ?
			if ((p3 - p2).cross(H - p2).dot(normal) < 0)
			{
				return false;
			}
			// hit rechts van p3 en p1 ?
			if ((p1 - p3).cross(H - p3).dot(normal) < 0)
			{
				return false;
			}

			initialize_hit(output_hit, ray, t);
			return true;
		}
	};
}

Primitive raytracer::primitives::triangle(const Point3D& p1, const Point3D& p2, const Point3D& p3)
{
	return Primitive(std::make_shared<TriangleImplementation>(p1,p2,p3));
}