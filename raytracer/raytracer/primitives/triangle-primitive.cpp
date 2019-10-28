#include "primitives/triangle-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	protected:
		const Point3D p1, p2 ,p3;

		TriangleImplementation(
			const Point3D& p11, const Point3D& p22,const Point3D& p33)
			: p1(p11), p2(p22), p3(p33)
		{
			
		}

		void initialize_hit(Hit* hit, const Ray& ray, double t) const
		{

		};

	public:
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			
		}
	};
}

Primitive raytracer::primitives::triangle()
{
	return Primitive(std::make_shared<TriangleImplementation>());
}