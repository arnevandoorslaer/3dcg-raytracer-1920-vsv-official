#include "samplers/random-sampler.h"
#include <random>

using namespace math;
using namespace raytracer;

namespace
{
	class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
	{
	public:
		RandomSampler(int sample_count) : m_sample_count(sample_count) { }

	private:
		int m_sample_count;

	public:
		void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
		{
			std::default_random_engine generator;
			std::uniform_real_distribution<double> distribution(0.0, 1.0);

			for (int i = 0; i < m_sample_count; i++) 
			{
				auto x = distribution(generator);
				auto y = distribution(generator);
				function(rectangle.from_relative(Point2D(x, y)));
			}
		}
	};
}

Sampler raytracer::samplers::random(int sample_count)
{
	return Sampler(std::make_shared<RandomSampler>(sample_count));
}
