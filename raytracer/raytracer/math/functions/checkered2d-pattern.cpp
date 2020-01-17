#include "math/functions/horizontal-lines-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;

Function<bool(const Point2D&)> math::functions::checkered2d()
{
	std::function<bool(const Point2D&)> function = [](const Point2D& p)
	{
		auto x = p.x();
		auto y = p.y();
		auto factor = 1;


		if (y < 0 && x < 0) {
			x = -x;
			y = -y;
		}
		else if (x < 0) {
			factor = -factor;
			x = -x;
		}
		else if (y < 0) {
			factor = -factor;
			y = -y;
		}

		int X = round(x);
		int Y = round(y);
		
		return factor * ((X + Y) % 2) == 0;
	};

	return from_lambda<bool, const Point2D&>(function);
}