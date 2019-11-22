#include "lights/spot-light.h"

using namespace math;
using namespace imaging;
using namespace raytracer;

namespace
{
	class SpotLight : public lights::_private_::LightSourceImplementation
	{
	public:
		SpotLight(const Point3D& position, const Vector3D& direction, const Angle& angle, const Color& color)
			:position(position), direction(direction), theta(angle), color(color) { }

	protected:
		std::vector<LightRay> lightrays_to(const Point3D& point) const override
		{
			auto u = (point - position).normalized();
			const auto cos_alpha = u.dot(direction);
			const auto cos_beta = cos(theta / 2);

			if (cos_alpha >= cos_beta )
			{
				auto ray = Ray(position, point);
				return std::vector<LightRay> {LightRay(ray, color)};
			}
			return std::vector<LightRay>{};
		}

	private:
		Point3D position;
		Vector3D direction;
		Angle theta;
		Color color;
	};
}

LightSource lights::spot(const Point3D& position, const Point3D& shine_at, const Angle& angle, const Color& color)
{
	return LightSource(std::make_shared<SpotLight>(position, (shine_at-position).normalized(), angle, color));
}