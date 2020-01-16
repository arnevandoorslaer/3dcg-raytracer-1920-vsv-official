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

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			// denom d
			double d = ray.direction.dot(m_normal);

			// If d == 0, no intersection 
			if (d != approx(0.0) && bounding_box().is_hit_by(ray))
			{
				// numer n
				double n = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));
				// Compute t
				double t = n / d;
				// Create hit object
				auto hit = std::make_shared<Hit>();
				// hit maken
				initialize_hit(hit.get(), ray, t);
				if (bounding_box().contains(hit->position)) {
					// in de lijst toevoegen
					hits.push_back(hit);
				}
			}
			return hits;
		}

		bool find_first_positive_hit(const Ray& ray, Hit* output_hit) const override
		{
			// denom d
			double d = ray.direction.dot(m_normal);

			// If d == 0, no intersection
			if (d != approx(0.0))
			{
				// numer n
				double n = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

				// t berekenen
				double t = n / d;
				if (t < 0 || t >= output_hit->t) return false;
				// initialiseer hit
				initialize_hit(output_hit, ray, t);

				if (bounding_box().contains(output_hit->position)) {
					// steek in lijst
					return true;
				}
			}
			return false;
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

	class SquareXZImplementation : public CoordinatePlaneImplementation {

	public:

		SquareXZImplementation() : CoordinatePlaneImplementation(Vector3D(0, 1, 0)) {

		}

		Box bounding_box() const override
		{
			return Box(interval(-1.0, 1.0), interval(-0.01, 0.01), interval(-1.0, 1.0));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
			hit->normal = ray.origin.y() > 0 ? m_normal : -m_normal;
		}
	};

	class SquareYZImplementation : public CoordinatePlaneImplementation {

	public:

		SquareYZImplementation() : CoordinatePlaneImplementation(Vector3D(1, 0, 0)) {

		}

		Box bounding_box() const override
		{
			return Box(interval(-0.01, 0.01), interval(-1.0, 1.0), interval(-1.0, 1.0));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
			hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
		}
	};
}

Primitive raytracer::primitives::xy_square() {
	return Primitive(std::make_shared<SquareXYImplementation>());
}
Primitive raytracer::primitives::xz_square() {
	return Primitive(std::make_shared<SquareXZImplementation>());
}

Primitive raytracer::primitives::yz_square() {
	return Primitive(std::make_shared<SquareYZImplementation>());
}