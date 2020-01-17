#include "math/functions/easing/elastic-easing-function.h"
#include "math/interval.h"
#include <assert.h>
# define M_PI           3.14159265358979323846  /* pi */

using namespace math;
using namespace math::functions;

EasingFunction math::functions::easing::elastic(int b, int a) {

	std::function<double(double)> lambda = [a, b](double t) {
		assert(interval(0.0, 1.0).contains(t));
		return -exp(-(a)* t) * cos(b * M_PI * t) + 1;
	};

	return from_lambda(lambda);
}