#include "primitives/square-primitive.h"

using namespace raytracer;
using namespace math;

using namespace primitives;


namespace
{

	class CoordinatePlaneImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	protected:
		const Vector3D m_normal;

		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="normal">
		/// Normal vector on plane. Needs to have unit length.
		/// </param>
		CoordinatePlaneImplementation(const Vector3D& normal)
			: m_normal(normal)
		{
			assert(normal.is_unit());
		}

		virtual void initialize_hit(Hit* hit, const Ray& ray, double t) const = 0;

	public:
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override {

			std::vector<std::shared_ptr<Hit>> hits;

			// Compute denominator
			double denom = ray.direction.dot(m_normal);

			// If denominator == 0, there is no intersection (ray runs parallel to plane)
			if (denom != approx(0.0))
			{
				// Compute numerator
				double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

				// Compute t
				double t = numer / denom;

				// Create hit object
				auto hit = std::make_shared<Hit>();

				// shared_ptr<T>::get() returns the T* inside the shared pointer
				initialize_hit(hit.get(), ray, t);

				if (hit->position.x() < 1 && hit->position.x() > -1) {
					if (hit->position.y() < 1 && hit->position.y() > -1) {
						// Put hit in list
						hits.push_back(hit);
					}
				}
			}

			return hits;

		}
	};

	class SquareXYImplementation : public CoordinatePlaneImplementation {

	public:

		SquareXYImplementation() : CoordinatePlaneImplementation(Vector3D(0, 0, 1)) {

		}

		Box bounding_box() const override
		{
			return Box(interval(-1.0, 1.0), interval(-1.0, 1.0), interval(-0.01, 0.01));
		}


	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
		}
	};
}

Primitive raytracer::primitives::xy_square() {
	return Primitive(std::make_shared<SquareXYImplementation>());
}