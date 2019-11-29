#include "lights/directional-light.h"

using namespace math;
using namespace raytracer;

namespace
{
	class DirectionalLight : public raytracer::lights::_private_::LightSourceImplementation
	{
	private:
		imaging::Color l_color;
		math::Vector3D l_direction;
	public:
		DirectionalLight(const math::Vector3D& direction, const imaging::Color& color)
			:l_direction(direction), l_color(color) {}

		std::vector<LightRay> lightrays_to(const math::Point3D& p) const override
		{
			std::vector<LightRay> rays;

			math::Ray ray(p - 10000 * l_direction, p);
			rays.push_back(LightRay(ray, l_color));

			return rays;
		}
	};
}

LightSource raytracer::lights::directionalLight(const math::Vector3D& direction, const imaging::Color& color)
{
	return LightSource(std::make_shared<DirectionalLight>(direction, color));
}