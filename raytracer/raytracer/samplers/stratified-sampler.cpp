#include "samplers/stratified-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;

namespace
{
	class StratifiedSampler : public samplers::_private_::SamplerImplementation
	{
		public:
			StratifiedSampler(const int& n, const int& m)
			{
				this->n = n;
				this->m = m;
			}

		private:
			int n;
			int m;

		public:
			void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
			{
				for (auto i = 0; i < n; i++)
				{
					for (auto j = 0; j < m; j++)
					{
						function(rectangle.from_relative(Point2D((1 / n) * (i + 0.5), (1 / m) * (j + 0.5))));
					}
				}
			}
	};
}

Sampler samplers::stratified(const int& n, const int& m)
{
	return Sampler(std::make_shared<StratifiedSampler>(n, m));
}