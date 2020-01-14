#include "samplers/multi-jittered-sampler.h"
#include <random>
#include <vector>

using namespace math;
using namespace raytracer;

namespace
{
	class MultiJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
	{
	public:
		MultiJitteredSampler(int n) {
			this->n = n;
		}
	private:
		int n;
	public:
		void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
		{

			std::default_random_engine generator;
			std::uniform_real_distribution<double> distribution(0.0, 1.0);

			std::vector<int> k_values;

			for (int i = 0; i != (this->n * this->n); i++)
			{
				k_values.push_back(i);
			}

			for (int i = 0; i != this->n; i++)
			{
				for (int j = 0; j != this->n; j++)
				{
					auto temp = distribution(generator);
					auto random_k = temp * k_values.size();
					int position = int(random_k);
					auto k_value = k_values.at(position);

					auto k_x = int(k_value / n);
					auto k_y = k_value % n;

					auto x = distribution(generator);
					auto y = distribution(generator);

					function(rectangle.from_relative(Point2D((i + (k_x + x) / n) / n, (j + (k_y + y) / n) / n)));

					k_values.erase(k_values.begin() + position);
				}
			}
		}
	};
}

Sampler raytracer::samplers::multiJittered(int n)
{
	return Sampler(std::make_shared<MultiJitteredSampler>(n));
}