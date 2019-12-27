#include "samplers/n-rooks-sampler.h"
#include <random>
#include <vector>

using namespace math;
using namespace raytracer;

namespace
{
	class NRooksSampler : public raytracer::samplers::_private_::SamplerImplementation
	{
	public:
		NRooksSampler(int n) {
			this->n = n;
		}
	private:
		int n;
	public:
		void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
		{
			std::vector<int> x_values;

			for (int i = 0; i != this->n; i++)
			{
				x_values.push_back(i);
			}

			std::default_random_engine generator;
			std::uniform_real_distribution<double> distribution(0.0, 1.0);

			for (int i = 0; i != this->n; i++)
			{
				auto temp = distribution(generator);
				auto rook_x_random = temp * x_values.size();
				int position = int(rook_x_random);
				auto rook_x_position = x_values.at(position);

				auto x = distribution(generator);
				auto y = distribution(generator);
				function(rectangle.from_relative(Point2D((rook_x_position + x) / n, (i + y) / n)));

				x_values.erase(x_values.begin() + position);
			}
		}
	};
}

Sampler raytracer::samplers::nRooks(int n)
{
	return Sampler(std::make_shared<NRooksSampler>(n));
}