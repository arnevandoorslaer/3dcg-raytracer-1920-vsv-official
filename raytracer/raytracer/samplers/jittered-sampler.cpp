#include "samplers/jittered-sampler.h"
#include <random>

using namespace math;
using namespace raytracer;

namespace
{
	class JitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
	{
		public:
			JitteredSampler(int n, int m) 
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

				std::default_random_engine generator;
				std::uniform_real_distribution<double> distribution(0.0, 1.0);

				for (int i = 0; i != this->n; i++)
				{
					for (int j = 0; j != this->m; j++)
					{
						auto x = distribution(generator);
						auto y = distribution(generator);
						function(rectangle.from_relative(Point2D((x + i) / n, (y + j) / m)));
					}
				}
			}
		};
}

Sampler raytracer::samplers::jittered(int n, int m)
{
	return Sampler(std::make_shared<JitteredSampler>(n, m));
}